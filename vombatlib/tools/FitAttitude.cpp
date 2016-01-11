#include "FitAttitude.h"
#include <qPCL/PclUtils/utils/cc2sm.h>

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
    ccHObject::Container entities;
    this->getSelectedEntitiesThatAreCCPointCloud(entities);

    ccHObject::Container polylines;
    this->getSelectedEntitiesThatAre(CC_TYPES::POLY_LINE, polylines);




    DLOG(INFO) << "found " << entities.size() << " point clouds";

    //convert them to pcl point clouds
    std::vector<ccPointCloud*> clouds;
    for (ccHObject* ent : entities) {
        ccPointCloud* cloud = ccHObjectCaster::ToPointCloud(ent);
        clouds.push_back(cloud);
    }

    for (ccHObject* ent : polylines) {
        ccPolyline* pline = ccHObjectCaster::ToPolyline(ent);
        ccPointCloud * verts = dynamic_cast<ccPointCloud *> (pline->getAssociatedCloud());
        if (verts)
            clouds.push_back(verts);
    }

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
        std::cout << "NOT CONVERGED!" << std::endl;
        return 0;
    }

    //    std::cout << "ended optimizing" << std::endl;

    std::vector<spc::Attitude> atts;
    atts = estimator.getEstimatedAttitudes();

    //now for each entity we send back an object for visualizing the result
    int id = 0;
    for (spc::Attitude att : atts) {

        LOG(INFO) << "attitude is in place: " << att.getPosition();
        ccAttitude* ccAtt = new ccAttitude(att);
        //        std::cout <<"NORMAL: \n" << att.getUnitNormal() << std::endl;
        //        std::cout <<"CENTER: \n" << att.getPosition() << std::endl;

        ccAtt->setVisible(true);

        entities.at(id)->addChild(ccAtt);

        //        QString name  = suggestHObjectIncrementalName(ccAtt, "Attitude");
        ccAtt->setName(ccAtt->getAttitude()->getDipAndDipAngleAsString().c_str());

        entityHasChanged(entities.at(id++));

        newEntity(ccAtt);
    }

    return 1;
}

ccAttitude *FitAttitude::fitAttitude(const ccHObject::Container &fittable)
{
    //convert them to pcl point clouds
    std::vector<ccPointCloud*> clouds;
    for (ccHObject* ent : fittable)
    {
        ccPointCloud* cloud = ccHObjectCaster::ToPointCloud(ent);
        if (cloud)
            clouds.push_back(cloud);

        else
        {
            ccPolyline* pline = ccHObjectCaster::ToPolyline(ent);
            if (pline)
            {
                ccPointCloud * verts = dynamic_cast<ccPointCloud *> (pline->getAssociatedCloud());
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
        LOG(WARNING) <<  "NOT CONVERGED!";
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
