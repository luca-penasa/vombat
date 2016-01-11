#include "Analyzer.h"
#include <spc/elements/VirtualOutcrop.h>
#include <ccVirtualOutcrop.h>
#include <ccSingleAttitudeModel.h>
#include <vombat.h>

#include <AnalyzerDlg.h>
#include <spc/elements/SelectionRubberband.h>

#include <ccPlanarSelection.h>

#include <ccHObjectCaster.h>
#include <ccPolyline.h>
#include <spc/methods/EstimatorAttitude.h>
#include <FitAttitude.h>

#include <ccAttitude.h>
#include <ccoutofcore/ccVirtualOutcrop.h>

#include <ccSingleAttitudeModel.h>
Analyzer::Analyzer(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Perform geological analysis of CC objects",
                                   "Perform geological analysis of CC objects",
                                   "Perform geological analysis of CC objects",
                                   ":/toolbar/icons/analyzer.png"),
                 parent_plugin)
{
    this->setShowProgressBar(false);
}

int Analyzer::compute()
{

    ccHObject::Container outcrops = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::VirtualOutcrop::Type);

    if (outcrops.size() > 1 )
    {
        LOG(INFO) << "please select only one virtual outcrop on which to operate";
        return 1;
    }

    else if (outcrops.size() == 1)
    {
        m_root_outcrop = dynamic_cast<ccVirtualOutcrop *>(outcrops.at(0));
    }
    else
        m_root_outcrop = new ccVirtualOutcrop();


    ccHObject::Container regions = m_dialog->getRegions();

    //    ccHObject::Container clouds = m_dialog->getClouds();

    ccHObject::Container traces = m_dialog->getTraces();

    LOG(INFO) << "found " << regions.size()  << " to be processed";
//    LOG(INFO) << "Found " << clouds.size() << " point clouds to be analyzed";
    LOG(INFO) << "Found " << traces.size() << " polylines";


    //    if (m_dialog->generateRegions())

    // first create selections out of regions
    for (ccHObject * obj : regions)
    {
        ccPolyline * line = ccHObjectCaster::ToPolyline(obj);

        ccPlanarSelection * sel = ccPlanarSelection::fromPolyline(*line);
        sel->setVisible(true);
//        if (m_dialog->generateRegions())
            m_root_outcrop->addChild(sel);


        ccHObject::Container  fittables;

        // for each region we crop polylines
        for (ccHObject * trace: traces)
        {
            ccPolyline * pline =  ccHObjectCaster::ToPolyline(trace);

            ccPointCloud * vertices = dynamic_cast<ccPointCloud *> (pline->getAssociatedCloud());

            ccPointCloud * cropped_vertices = sel->crop(vertices);

            if (cropped_vertices)
            {
                ccPolyline *cropped_pline = new ccPolyline(cropped_vertices);
                for (int i = 0 ; i < cropped_vertices->size(); ++i)
                {
                    LOG(INFO) << cropped_vertices->getPoint(i)->x;
                }

                cropped_pline->addPointIndex(0, cropped_vertices->size()-1);
                cropped_pline->setVisible(true);
                if (m_dialog->cropStrataTraces())
                    sel->addChild(cropped_pline);
            }

            fittables.push_back(cropped_vertices);
        }

        ccAttitude * attitude = FitAttitude::fitAttitude(fittables);
        if (m_dialog->outputAttitudes())
            sel->addChild(attitude);


        if (m_dialog->outputRulers())
        {

            spc::StratigraphicModelSingleAttitude::Ptr spcmodel( new spc::StratigraphicModelSingleAttitude( *attitude->getAttitude()));
            ccSingleAttitudeModel * model = new ccSingleAttitudeModel(spcmodel);

            sel->addChild(model);
        }

    }



    newEntity(m_root_outcrop);


    return 1;
}

int Analyzer::checkSelected()
{
    // if (vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::SelectionRubberband::Type).size() >=1)
    return 1;
    // else
    //     return 0;
}

int Analyzer::openInputDialog()
{

    if (!m_dialog)
        m_dialog =  new AnalyzerDlg(vombat::theInstance()->getMainWindow());


    m_dialog->clearCombos();
    m_dialog->populateCombos();


    return m_dialog->exec() ? 1 : 0;


    //    return 1;
}
