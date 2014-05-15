#include "ccCalibrationDB.h"
#include <iostream>






ccCalibrationDB::ccCalibrationDB()
{
    initMetadata();
}


void ccCalibrationDB::rebuildClouds()
{
    std::vector<ccPointCloud *> clouds = ccCalibrationDB::getAsPointClouds(*(this->getAsSpc()));

    BOOST_FOREACH(ccPointCloud * cloud, clouds)
    {
        this->addChild(cloud);
        cloud->setLocked(true);
    }
}





void ccCalibrationDB::initMetadata()
{
    QVariant var("Input database for intensity calibration.");
    setMetaData(QString("[vombat][ccCalibrationDB]"), var);
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





