#include "ccCalibrationDB.h"
#include <iostream>

#include <Eigen/Dense>




ccCalibrationDB::ccCalibrationDB()
{

}


void ccCalibrationDB::rebuildClouds()
{
    std::vector<ccPointCloud *> clouds = ccCalibrationDB::getAsPointClouds(*(this->getAsSpc()));

    spcForEachMacro(ccPointCloud * cloud, clouds)
    {
        this->addChild(cloud);
        cloud->setLocked(true);
    }
}




void ccCalibrationDB::drawMeOnly(CC_DRAW_CONTEXT &context)
{

}

void ccCalibrationDB::applyGLTransformation(const ccGLMatrix &trans)
{





}

void ccCalibrationDB::setGLTransformation(const ccGLMatrix &trans)
{


}







std::vector<ccPointCloud *> ccCalibrationDB::getAsPointClouds(const spc::DataDB &db)
{
    size_t n_clouds = db.getNumberOfDifferentClouds();
    std::vector<ccPointCloud * > out(n_clouds);
    spcForEachMacro(ccPointCloud * &cloud, out)
    {
        cloud = new ccPointCloud(); //we need them instantiated

        ccScalarField * distance = new ccScalarField();
        distance->setName("distance");

        ccScalarField * angle = new ccScalarField();
        angle->setName("angle");

        ccScalarField * intensity = new ccScalarField();
        intensity->setName("intensity");

        cloud->addScalarField(distance);
        cloud->addScalarField(angle);
        cloud->addScalarField(intensity);
    }



    spcForEachMacro(spc::CorePoint::Ptr core, db.getDataDB())
    {

        Eigen::Vector3f center = core->value<Eigen::Vector3f>("centroid");
        CCVector3 p (center(0), center(1), center(2));

        ccPointCloud * cloud = out.at(core->value<size_t>("cloud_id"));

        float distance, angle, intensity;
        distance = core->value<float>("distance");
        angle = core->value<float>("angle");
        intensity = core->value<float>("intensity");

        std::string name =core->value<std::string>("cloud_name");

        cloud->setName(name.c_str());


        cloud->reserve(cloud->size() + 1);

        cloud->getScalarField(cloud->getScalarFieldIndexByName("distance"))->addElement(distance);
        cloud->getScalarField(cloud->getScalarFieldIndexByName("angle"))->addElement(angle);
        cloud->getScalarField(cloud->getScalarFieldIndexByName("intensity"))->addElement(intensity);

        cloud->getScalarField(cloud->getScalarFieldIndexByName("distance"))->computeMinAndMax();
        cloud->getScalarField(cloud->getScalarFieldIndexByName("angle"))->computeMinAndMax();
        cloud->getScalarField(cloud->getScalarFieldIndexByName("intensity"))->computeMinAndMax();

        cloud->addPoint(p);

    }

    return out;
}
