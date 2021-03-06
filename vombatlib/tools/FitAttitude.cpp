#include "FitAttitude.h"
//#include <qPCL/PclUtils/utils/cc2sm.h>

#include <ccoutofcore/ccSingleAttitudeModel.h>

//#include <ccArrow.h>

#include <ccHObjectCaster.h>

#include <ccoutofcore/ccAttitude.h>

#include <spc/methods/EstimatorAttitude.h>
#include <boost/foreach.hpp>

#include <helpers/qtHelper.h>
#include <helpers/spcCCPointCloud.h>
#include <ccAttitude.h>
#include <ccPolyline.h>
#include <spcCCPointCloud.h>

#include <ccFitAttitudeDlg.h>

#include <vombat.h>
#include <spc/elements/Attitude.h>

FitAttitude::FitAttitude(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Fit A geological orientation",
                     "Fit a geological orientation",
                     "Use a set of points to fit a geological orientation",
                     ":/toolbar/icons/attitude.png"),
          parent_plugin)
{
    this->setShowProgressBar(false);
}

int FitAttitude::compute()
{

    if (!m_dlg)
        return -1;

    ccHObject::Container entities;
    this->getSelectedEntitiesThatAreCCPointCloud(entities);

    ccHObject::Container polylines;
    this->getSelectedEntitiesThatAre(CC_TYPES::POLY_LINE, polylines);

    DLOG(INFO) << "found " << entities.size() << " point clouds";

    DLOG(INFO) << "found " << polylines.size() << " polylines";

    //convert them to pcl point clouds
    std::vector<ccPointCloud*> clouds;

    ccHObject::Container used_ents;

    for (ccHObject* ent : entities) {
        ccPointCloud* cloud = ccHObjectCaster::ToPointCloud(ent);
        clouds.push_back(cloud);

        used_ents.push_back(ent);
    }

    for (ccHObject* ent : polylines) {
        ccPolyline* pline = ccHObjectCaster::ToPolyline(ent);
        ccPointCloud* verts = dynamic_cast<ccPointCloud*>(pline->getAssociatedCloud());
        if (verts)
        {
            clouds.push_back(verts);
            DLOG(INFO) << "pushed back polyline with " << verts->size() << "points";

            used_ents.push_back(ent);
        }


    }




    // fitting all atts in an unique normal
    if (m_dlg->isUniqueNormal()) {

        DLOG(INFO) << "creating estimator";
        //set up an estimator
        spc::AttitudeEstimator<float> estimator;

        for (ccPointCloud* cloud : clouds) //add the single clouds
        {
            spcCCPointCloud::Ptr c = spcCCPointCloud::fromccPointCloud(cloud);
            estimator.addInputCloud(c);
        }

        //    std::cout << "starting opimization" << std::endl;

        int status = estimator.estimate();

        if (status == 0) {
            LOG(WARNING) << "NOT CONVERGED!";
            return 0;
        }

        DLOG(INFO) << "estimation done";

        std::vector<spc::Attitude> atts;
        atts = estimator.getEstimatedAttitudes();

//        DLOG(INFO) << "got n " << atts.size() << " attitudes";

        //now for each entity we send back an object for visualizing the result
        int id = 0;
        for (spc::Attitude att : atts) {

//            DLOG(INFO) << "attitude is in place: " << att.getPosition();
            ccAttitude* ccAtt = new ccAttitude(att);


//            DLOG(INFO) << "attitude created. ";
            ccAtt->setVisible(true);

//            newEntity(ccAtt);
//            DLOG(INFO) << "now visible. ";

//            DLOG(INFO) << "going to add the child ";
            used_ents.at(id)->addChild(ccAtt);

//            DLOG(INFO) << "added child ";
            ccAtt->setName(ccAtt->getAttitude()->getDipAndDipAngleAsString().c_str());

//            DLOG(INFO) << "notfy changes. ";
            entityHasChanged(used_ents.at(id++));

//            DLOG( INFO)  << "calling new entity!";
            newEntity(ccAtt);
//            DLOG(INFO) << "called new entity for " << ccAtt->getName().toStdString();
        }
    }
    else // each attitude individually
    {
        for (ccPointCloud* cloud : clouds) //add the single clouds
        {
            spcCCPointCloud::Ptr c = spcCCPointCloud::fromccPointCloud(cloud);
            Vector3D  n ;
            n.normalFromBestFit(*c);

            Eigen::Vector3f cent = c->getCentroid();

            spc::Attitude::Ptr att (new spc::Attitude);

            att->setNormal(n.getUnitNormal());
            att->setPosition(cent);

            ccAttitude* ccAtt = new ccAttitude(att);

            ccAtt->setVisible(true);
            cloud->addChild(ccAtt);
            ccAtt->setName(ccAtt->getAttitude()->getDipAndDipAngleAsString().c_str());
//            entityHasChanged(cloud);
            newEntity(ccAtt);
        }
    }

    return 1;
}

ccAttitude* FitAttitude::fitAttitude(const ccHObject::Container& fittable)
{

    //convert them to pcl point clouds
    std::vector<ccPointCloud*> clouds;
    for (ccHObject* ent : fittable) {
        ccPointCloud* cloud = ccHObjectCaster::ToPointCloud(ent);
        if (cloud)
            clouds.push_back(cloud);

        else {
            ccPolyline* pline = ccHObjectCaster::ToPolyline(ent);
            if (pline) {
                ccPointCloud* verts = dynamic_cast<ccPointCloud*>(pline->getAssociatedCloud());
                clouds.push_back(verts);
            }
        }
    }

    //set up an estimator
    spc::AttitudeEstimator<float> estimator;

    for (ccPointCloud* cloud : clouds) //add the single clouds
    {
        spcCCPointCloud::Ptr c = spcCCPointCloud::fromccPointCloud(cloud);
        estimator.addInputCloud(c);
    }

    int status = estimator.estimate();

    if (status == 0) {
        LOG(WARNING) << "NOT CONVERGED!";
        return 0;
    }

    spc::Attitude att = estimator.getEstimatedAttitude(true);

    LOG(INFO) << "attitude is in place: " << att.getPosition();
    ccAttitude* ccAtt = new ccAttitude(att);

    ccAtt->setVisible(true);

    return ccAtt;
}

int FitAttitude::checkSelected()
{
    ccHObject::Container ents, planes, polys;
    getSelectedEntitiesThatAre(CC_TYPES::POINT_CLOUD, ents);
    getSelectedEntitiesThatAre(CC_TYPES::POLY_LINE, polys);

    if (ents.size() > 0 || polys.size() > 0)
        return 1;
    else
        return -1;
}

int FitAttitude::openInputDialog()
{

    if (!m_dlg)
        m_dlg = new ccFitAttitudeDlg();

    return m_dlg->exec();
}
