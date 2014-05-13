#include "ComputeCalibrationDB.h"
//#include <spcCCPointCloud.h>

#include <ccoutofcore/ccCalibrationDB.h>
#include <spc/calibration/CalibrationDataEstimator.h>

#include <iostream>


ComputeCalibrationDB::ComputeCalibrationDB(ccPluginInterface *parent_plugin): BaseFilter(FilterDescription(   "Compute a calibration DB object for intensity calibration",
                                                                                                              "Compute a calibration DB object for intensity calibration",
                                                                                                              "Compute a calibration DB object for intensity calibration",
                                                                                                              ":/toolbar/icons/calibrationDB.png"), parent_plugin),
    m_dialog(0)
{
    this->setShowProgressBar(true);
}



int ComputeCalibrationDB::compute()
{



    spc::CalibrationDataEstimator calibrator;
    calibrator.setInputClouds(m_dialog->getPCDFiles());
    calibrator.setInputCorePoints(m_dialog->getKeypointsFile());


    if (m_dialog->usePrecomputedNormals())
    {
        calibrator.setInputNormalsCloudName(m_dialog->getNormalsFile());
        calibrator.setNormalEstimationMethod(spc::CalibrationDataEstimator::PRECOMPUTED_NORMALS);
        calibrator.setMaximumDistanceForGettingNormal(m_dialog->getMaxDistanceForNormals());
    }

    calibrator.setSearchRadius(m_dialog->getKernelSize());

    //we use gaussian by def
    calibrator.setIntensityEstimationMethod(spc::CalibrationDataEstimator::GAUSSIAN_ESTIMATION);
    calibrator.setIntensityGaussianSpatialSigma(m_dialog->getKernelSize());


    calibrator.compute();


    ccCalibrationDB * calib_db = new ccCalibrationDB(calibrator.getCalibrationDB().getValidDataOnly());


    calib_db->setName("CalibrationDB");
    calib_db->setVisible(true);

    std::vector<ccPointCloud *> clouds = CalibrationDBAsPointClouds(*(calib_db->getAsSpc()));

    BOOST_FOREACH(ccPointCloud * cloud, clouds)
    {
        calib_db->addChild(cloud);
    }

    newEntity(calib_db);





    return 1;
}




int ComputeCalibrationDB::checkSelected()
{
    return true;
}


int ComputeCalibrationDB::openInputDialog()
{

    if (!m_dialog)
        m_dialog = new ComputeCalibrationDBDlg(0);


    //    ccPointCloud * cloud = getSelectedEntityAsCCPointCloud();

    //    m_dialog->getUI()->comboDistance->addItemsFromFieldsCloud(cloud);
    //    m_dialog->getUI()->comboIntensity->addItemsFromFieldsCloud(cloud);



    /// we need to init the dialog

    return m_dialog->exec() ? 1 : 0;

}

std::vector<ccPointCloud *> ComputeCalibrationDB::CalibrationDBAsPointClouds(const spc::CalibrationDataDB &db)
{
    size_t n_clouds = db.getNumberOfDifferentClouds();
    std::vector<ccPointCloud * > out(n_clouds);
    BOOST_FOREACH(ccPointCloud * &cloud, out)
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



    BOOST_FOREACH(spc::CorePointData::Ptr core, db.getDataDB())
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
