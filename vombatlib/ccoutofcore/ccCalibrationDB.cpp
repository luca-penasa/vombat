#include "ccCalibrationDB.h"
#include <iostream>

#include <Eigen/Dense>

#include <ccoutofcore/ccSample.h>
#include <spc/elements/SamplesDB.h>


ccCalibrationDB::ccCalibrationDB()
{
        writeSPCClassNameToMetadata();
}


//void ccCalibrationDB::exposeSamples()
//{

//    size_t n = m_calibration_db_->getNumberOfDifferentClouds();

//    for (int i = 0; i < n; ++i)
//    {
//        std::cout << "cloud id " << i << std::endl;
//        std::vector<spc::Sample::Ptr> v = m_calibration_db_->getDataWithValue("cloud_id", i);
//        std::stringstream stream;
//        stream << "Cloud id: " << i;
//        ccHObject * obj  = new ccHObject (QString(stream.str().c_str()) );

//        spcForEachMacro(spc::Sample::Ptr s, v)
//        {
//            ccSample * sample = new ccSample(s);
//            sample->setLocked(true);
//            sample->setEnabled(true);
//            sample->setVisible(true);
//            obj->addChild(sample);

//        }
//        this->addChild(obj);
//    }
//}

//std::vector<ccPointCloud *> ccCalibrationDB::getAsPointClouds(const spc::SamplesDB &db)
//{
//    size_t n_clouds = db.getNumberOfDifferentClouds();
//    std::vector<ccPointCloud * > out(n_clouds);
//    spcForEachMacro(ccPointCloud * &cloud, out)
//    {
//        cloud = new ccPointCloud(); //we need them instantiated

//        ccScalarField * distance = new ccScalarField();
//        distance->setName("distance");

//        ccScalarField * angle = new ccScalarField();
//        angle->setName("angle");

//        ccScalarField * intensity = new ccScalarField();
//        intensity->setName("intensity");

//        cloud->addScalarField(distance);
//        cloud->addScalarField(angle);
//        cloud->addScalarField(intensity);
//    }



//    spcForEachMacro(spc::Sample::Ptr core, db.getSamplesDB())
//    {

//        Eigen::Vector3f center = core->value<Eigen::Vector3f>("centroid");
//        CCVector3 p (center(0), center(1), center(2));

//        ccPointCloud * cloud = out.at(core->value<size_t>("cloud_id"));

//        float distance, angle, intensity;
//        distance = core->value<float>("distance");
//        angle = core->value<float>("angle");
//        intensity = core->value<float>("intensity");

//        std::string name =core->value<std::string>("cloud_name");

//        cloud->setName(name.c_str());


//        cloud->reserve(cloud->size() + 1);

//        cloud->getScalarField(cloud->getScalarFieldIndexByName("distance"))->addElement(distance);
//        cloud->getScalarField(cloud->getScalarFieldIndexByName("angle"))->addElement(angle);
//        cloud->getScalarField(cloud->getScalarFieldIndexByName("intensity"))->addElement(intensity);

//        cloud->getScalarField(cloud->getScalarFieldIndexByName("distance"))->computeMinAndMax();
//        cloud->getScalarField(cloud->getScalarFieldIndexByName("angle"))->computeMinAndMax();
//        cloud->getScalarField(cloud->getScalarFieldIndexByName("intensity"))->computeMinAndMax();

//        cloud->addPoint(p);

//    }

//    return out;
//}
