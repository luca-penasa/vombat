#include "Cropper.h"
#include <spc/elements/VirtualOutcrop.h>
#include <ccVirtualOutcrop.h>
#include <ccSingleAttitudeModel.h>
#include <vombat.h>

#include <CropperDlg.h>
#include <spc/elements/SelectionRubberband.h>

#include <ccPlanarSelection.h>

#include <ccHObjectCaster.h>
#include <ccPolyline.h>
#include <spc/methods/EstimatorAttitude.h>
#include <FitAttitude.h>

#include <ccAttitude.h>
#include <ccoutofcore/ccVirtualOutcrop.h>
#include <spcCCPointCloud.h>
#include <ccSingleAttitudeModel.h>

#include <spc/methods/SelectionExtractor.h>

Cropper::Cropper(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Crop entities using a rubberband",
                                   "Crop entities using a rubberband",
                                   "Crop entities using a rubberband",
                                   ":/toolbar/icons/cropper.png"),
                 parent_plugin)
{
    this->setShowProgressBar(false);
}

int Cropper::compute()
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


    ccHObject::Container selections = m_dialog->getSelections();

    //    ccHObject::Container clouds = m_dialog->getClouds();

    ccHObject::Container croppables = m_dialog->getCroppables();

    LOG(INFO) << "found " << selections.size()  << " to be processed";
//    LOG(INFO) << "Found " << clouds.size() << " point clouds to be analyzed";
    LOG(INFO) << "Found " << croppables.size() << " polylines";


    //    if (m_dialog->generateRegions())

    // first create selections out of regions
    for (ccHObject * obj : selections)
    {

        ccPlanarSelection * sel = dynamic_cast<ccPlanarSelection *> (obj);

        for (ccHObject * to_crop : croppables)
        {
            if (to_crop->isA(CC_TYPES::POLY_LINE))
            {
                ccPolyline * pline =  ccHObjectCaster::ToPolyline(to_crop);

                ccPointCloud * vertices = dynamic_cast<ccPointCloud *> (pline->getAssociatedCloud());

                ccPointCloud * cropped_vertices = sel->crop(vertices);

                if (cropped_vertices)
                {
                    ccPolyline *cropped_pline = new ccPolyline(cropped_vertices);

                    cropped_pline->addPointIndex(0, cropped_vertices->size()-1);
                    cropped_pline->setVisible(true);
//                    if (m_dialog->cropStrataTraces())
                        sel->addChild(cropped_pline);
                }


            }

            else if (to_crop->isA(CC_TYPES::POINT_CLOUD))
            {

                ccPointCloud * cloud = ccHObjectCaster::ToPointCloud(to_crop);

//                ccPointCloud * cropped = sel->crop(cloud);

//                if (cropped)
//                    sel->addChild(cropped);






//                spc::SelectionRubberband::Ptr spcsel = sel->getSPCElement<spc::SelectionRubberband>();

//                Eigen::Transform<float, 3, Affine, AutoAlign> T = spcsel->getPojectionTransform();

//                ccPointCloud * newpoincloud = new ccPointCloud;
//                newpoincloud->reserve(cloud->size());

//                for (int i =  0 ; i < cloud->size(); ++i)
//                {
//                    CCVector3 * p =  const_cast<CCVector3 *>(cloud->getPoint(i));
//                    Eigen::Vector3f point = Eigen::Map<Eigen::Vector3f>(&(p->x));
//                    Eigen::Vector3f newp  = T*point;

//                    point = newp;

//                    CCVector3 nps (newp(0), newp(1), 0);

//                    newpoincloud->addPoint(nps);


//                }

//                sel->addChild(newpoincloud);
//                newEntity(newpoincloud);








                spc::PointCloudBase::Ptr asspc =  spcCCPointCloud::fromccPointCloud(cloud);

                spc::SelectionExtractor<Eigen::Vector3f, int> ext;
                ext.setInputSet(asspc);

                ext.setSelection(sel->getSPCElement<spc::SelectionBase<Eigen::Vector3f>>());

                ext.compute();


                std::vector<int> inside = ext.getInsideIds();


                if (inside.size() == 0)
                    continue;

                CCLib::ReferenceCloud * ref = new CCLib::ReferenceCloud (cloud);
                for (int i : inside)
                {
                    ref->addPointIndex(i);
                }


                ccPointCloud * outcloud  = cloud->partialClone(ref);

                sel->addChild(outcloud);
                newEntity(outcloud);



            }
        }
    }


//        ccPolyline * line = ccHObjectCaster::ToPolyline(obj);

//        ccPlanarSelection * sel = ccPlanarSelection::fromPolyline(*line);
//        sel->setVisible(true);
////        if (m_dialog->generateRegions())
//            m_root_outcrop->addChild(sel);


//        ccHObject::Container  fittables;

//        // for each region we crop polylines
//        for (ccHObject * trace: traces)
//        {
//            ccPolyline * pline =  ccHObjectCaster::ToPolyline(trace);

//            ccPointCloud * vertices = dynamic_cast<ccPointCloud *> (pline->getAssociatedCloud());

//            ccPointCloud * cropped_vertices = sel->crop(vertices);

//            if (cropped_vertices)
//            {
//                ccPolyline *cropped_pline = new ccPolyline(cropped_vertices);

//                cropped_pline->addPointIndex(0, cropped_vertices->size()-1);
//                cropped_pline->setVisible(true);
//                if (m_dialog->cropStrataTraces())
//                    sel->addChild(cropped_pline);
//            }

//            fittables.push_back(cropped_vertices);
//        }

//        ccAttitude * attitude = FitAttitude::fitAttitude(fittables);
//        if (m_dialog->outputAttitudes())
//            sel->addChild(attitude);


//        if (m_dialog->outputRulers())
//        {

//            spc::StratigraphicModelSingleAttitude::Ptr spcmodel( new spc::StratigraphicModelSingleAttitude( *attitude->getAttitude()));
//            ccSingleAttitudeModel * model = new ccSingleAttitudeModel(spcmodel);

//            sel->addChild(model);
//        }


//    }



//    newEntity(m_root_outcrop);


    return 1;
}

int Cropper::checkSelected()
{
    // if (vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::SelectionRubberband::Type).size() >=1)
    return 1;
    // else
    //     return 0;
}

int Cropper::openInputDialog()
{

    if (!m_dialog)
        m_dialog =  new CropperDlg(vombat::theInstance()->getMainWindow());


    m_dialog->clearCombos();
    m_dialog->populateCombos();


    return m_dialog->exec() ? 1 : 0;


    //    return 1;
}
