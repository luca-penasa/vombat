#include "ComputeCalibrationDB.h"
//#include <spcCCPointCloud.h>

#include <ccoutofcore/ccEigenTable.h>
#include <spc/methods/IntensityCalibrationDataEstimator.h>
#include <spc/methods/IntensityCalibrationDataFilter.h>

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
    calibrator.setInputSamples(m_dialog->getKeypointsFile());


    if (m_dialog->usePrecomputedNormals())
    {
        calibrator.setInputNormalsCloudName(m_dialog->getNormalsFile());
        calibrator.setNormalEstimationMethod(spc::CalibrationDataEstimator::PRECOMPUTED_NORMALS);
        calibrator.setMaximumDistanceForGettingNormal(m_dialog->getMaxDistanceForNormals());
    }

    calibrator.setNormalEstimationSearchRadius(m_dialog->getKernelSize());

    //we use gaussian by def
    calibrator.setIntensityEstimationMethod(spc::CalibrationDataEstimator::GAUSSIAN_ESTIMATION);
    calibrator.setIntensityGaussianSpatialSigma(m_dialog->getKernelSize());


    calibrator.compute();

    // now filter out data that are not good and add weights for the other
//    spc::IntensityCalibrationDataFilter filter;
//    filter.setData(calibrator.getCalibrationDB());
//    filter.setMinNNeighbors(10);

//    spc::EigenTable::Ptr data = filter.applyFilter();

    ccEigenTable * calib_db = new ccEigenTable(calibrator.getCalibrationDB());

//    std::cout << calibrator.getCalibrationDB()->mat() << std::endl;

    calib_db->setName("CalibrationDB");
    calib_db->setVisible(true);

//    calib_db->exposeSamples();



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


