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
    if (m_dialog->checkInputValidity() == false)
        return -21;

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

    calib_db->rebuildClouds();



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


