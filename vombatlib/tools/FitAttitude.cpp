#include "FitAttitude.h"
#include <qPCL/PclUtils/utils/cc2sm.h>


#include <ccoutofcore/ccSingleAttitudeModel.h>

//#include <ccArrow.h>

#include <ccHObjectCaster.h>

#include <ccoutofcore/ccAttitude.h>

#include <spc/methods/EstimatorAttitude.h>
#include <boost/foreach.hpp>

#include <helpers/qtHelper.h>



FitAttitude::FitAttitude(ccPluginInterface * parent_plugin): BaseFilter(FilterDescription(   "Fit A geological orientation",
                                                                                              "Fit a geological orientation",
                                                                                              "Use a set of points to fit a geological orientation",
                                                                                              ":/toolbar/icons/attitude.png")
                                                                                                        , parent_plugin)
{
    this->setShowProgressBar(false);
}

int
FitAttitude::compute()
{
    ccHObject::Container entities;
    this->getSelectedEntitiesThatAreCCPointCloud(entities);

    //convert them to pcl point clouds
    std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> clouds;
    spcForEachMacro( ccHObject * ent, entities)
    {
        ccPointCloud * cloud = ccHObjectCaster::ToPointCloud( ent );

        cc2smReader reader;
        reader.setInputCloud(cloud);
        pcl::PCLPointCloud2 sm_cloud = reader.getXYZ();

        pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_cloud (new pcl::PointCloud<pcl::PointXYZ>);

        pcl::fromPCLPointCloud2(sm_cloud, *pcl_cloud);

        clouds.push_back(pcl_cloud);

    }

    //set up an estimator
    spc::AttitudeEstimator estimator;

    spcForEachMacro(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, clouds) //add the single clouds
    {
        estimator.addInputCloud(cloud);

//        std::cout << "adding cloud with points: " << cloud->size() << std::endl;
    }

//    std::cout << "starting opimization" << std::endl;

    int status = estimator.estimate();

    if (status == 0)
    {
        std::cout << "NOT CONVERGED!" << std::endl;
        return 0;
    }

//    std::cout << "ended optimizing" << std::endl;


    std::vector<spc::Attitude> atts;
    atts = estimator.getEstimatedAttitudes();



    //now for each entity we send back an object for visualizing the result
    int id = 0;
    spcForEachMacro(spc::Attitude att, atts)
    {

        ccAttitude * ccAtt = new ccAttitude (att);
//        std::cout <<"NORMAL: \n" << att.getUnitNormal() << std::endl;
//        std::cout <<"CENTER: \n" << att.getPosition() << std::endl;

        ccAtt->setVisible(true);

        entities.at(id)->addChild(ccAtt);

//        QString name  = suggestHObjectIncrementalName(ccAtt, "Attitude");
        ccAtt->setName(ccAtt->getAttitude()->getDipAndDipAngleAsString().c_str());

        entityHasChanged( entities.at(id++));

        newEntity(ccAtt);
    }


    return 1;
}

int FitAttitude::checkSelected()
{
    ccHObject::Container ents, planes, polys;
    getSelectedEntitiesThatAre(CC_TYPES::POINT_CLOUD, ents);

    if (ents.size() > 0)
        return 1;
    else
        return -1;
}



