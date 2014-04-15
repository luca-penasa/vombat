#include "CalibrateDevice.h"
#include <spcCCPointCloud.h>
#include <ccoutofcore/ccTimeSeries.h>

#include <spc/devices/calibrate_discrete_points_model.h>
#include <ccoutofcore/cccalibrationmodel.h>

#include <iostream>


CalibrateDevice::CalibrateDevice(ccPluginInterface *parent_plugin): BaseFilter(FilterDescription(   "Estimate the parameters for device calibration",
                                                                                                    "Estimate the parameters for device calibration",
                                                                                                    "Estimate the parameters for device calibration",
                                                                                                    ":/toolbar/icons/device.png"), parent_plugin),
    m_dialog(0)
{
    this->setShowProgressBar(false);
}



int CalibrateDevice::compute()
{

    float bandwidth = m_dialog->getBandwidth();
    float s_step = m_dialog->getSamplingStep();

    std::string distance_n = m_dialog->getDistanceField();
    std::string intensity_n = m_dialog->getIntensityField();

    ccPointCloud * cloud = getSelectedEntityAsCCPointCloud();

    spcCCPointCloud::Ptr spc_cloud (new spcCCPointCloud (cloud));



    spc::CalibrateDiscretePointsModel calibrator;
    calibrator.setInputCloud(spc_cloud);
    calibrator.setBandwidth(bandwidth);
    calibrator.setSamplingStep(s_step);
    calibrator.setDistanceField(distance_n);
    calibrator.setIntensityField(intensity_n);
    calibrator.compute();



    spc::DiscretePointsCalibrationModel::Ptr model= calibrator.getModel();

    spc::GenericTimeSeries<float>::Ptr ts = model->getTS();


    ccTimeSeries * serie = new ccTimeSeries(ts);
    serie->setName("CorrectionTS");

    ccCalibrationModel *  mod = new ccCalibrationModel(model);

    mod->addChild(serie);


    newEntity(mod);



    return 1;
}




int CalibrateDevice::checkSelected()
{
    return isFirstSelectedCcPointCloud();
}


int CalibrateDevice::openInputDialog()
{

    m_dialog = new ccCalibrateDeviceDlg(0);


    ccPointCloud * cloud = getSelectedEntityAsCCPointCloud();

    m_dialog->getUI()->comboDistance->addItemsFromFieldsCloud(cloud);
    m_dialog->getUI()->comboIntensity->addItemsFromFieldsCloud(cloud);



    /// we need to init the dialog

    return m_dialog->exec() ? 1 : 0;

}
