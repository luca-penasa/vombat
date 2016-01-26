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

#include <QMainWindow>

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


    ccHObject::Container regions, traces, links;

    regions = m_dialog->comboRegions->getChildrenOfSelectedObject(CC_TYPES::POLY_LINE);

    traces = m_dialog->comboTraces->getChildrenOfSelectedObject(CC_TYPES::POLY_LINE);

    links = m_dialog->comboLinks->getChildrenOfSelectedObject(CC_TYPES::POLY_LINE);


    LOG(INFO) << "found " << regions.size()  << " to be processed";
    LOG(INFO) << "Found " << links.size() << " links";
    LOG(INFO) << "Found " << traces.size() << " polylines";


    //    if (m_dialog->generateRegions())

    // first create selections out of regions
    for (ccHObject * obj : regions)
    {
        ccPolyline * line = ccHObjectCaster::ToPolyline(obj);

        ccPlanarSelection * sel = ccPlanarSelection::fromPolyline(*line);
        sel->setVisible(true);
        sel->setDepth(m_dialog->spinRegionDepth->value());
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

                cropped_pline->addPointIndex(0, cropped_vertices->size()-1);
                cropped_pline->setVisible(true);
                if (m_dialog->checkBoxCropStrataTraces->checkState())
                    sel->addChild(cropped_pline);
            }

            fittables.push_back(cropped_vertices);
        }

        ccAttitude * attitude = FitAttitude::fitAttitude(fittables);
        if (m_dialog->checkBoxGenerateAttitudes->checkState())
            sel->addChild(attitude);


        if (m_dialog->checkBoxGenerateRulers->checkState())
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


    //    m_dialog->clearCombos();
    //    m_dialog->populateCombos();


    return m_dialog->exec() ? 1 : 0;


    //    return 1;
}
