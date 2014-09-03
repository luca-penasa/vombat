#include "CalibrateDevice.h"
#include <spcCCPointCloud.h>
#include <ccoutofcore/ccTimeSeries.h>

#include <spc/methods/IntensityCalibrationDiscretePointsModel.h>


#include <iostream>


#include <spc/methods/IntensityCalibration.h>

CalibrateDevice::CalibrateDevice(ccPluginInterface *parent_plugin)
    : BaseFilter(
          FilterDescription("Estimate the parameters for device calibration",
                            "Estimate the parameters for device calibration",
                            "Estimate the parameters for device calibration",
                            ":/toolbar/icons/device.png"),
          parent_plugin),
      m_dialog(0)
{
    this->setShowProgressBar(false);
}

int CalibrateDevice::compute()
{

    ccMyBaseObject *myobj = dynamic_cast
        <ccMyBaseObject *>(getSelectedEntityAsCCHObject());
    spc::IntensityCalibrator calibrator;

    spc::SamplesDB::Ptr db = spcDynamicPointerCast
        <spc::SamplesDB>(myobj->getSPCElement());

    spc::SamplesDB gooddb =  db->getNotNanEntries<float>("intensity").getNotNanEntries<float>("angle").getNotNanEntries<float>("distance");

    db = spcMakeSharedPtrMacro<spc::SamplesDB> (gooddb);

//    calibrator.setCalibrationSamplesDB(db);
    std::cout << "set the db" << std::endl;


    bool multiple_constants = m_dialog->getUI()->chkDifferent->isChecked();

    std::cout << "creating the model" << std::endl;
//    spc::JutzyModel::Ptr jutzy  (new spc::JutzyModel(db, !multiple_constants));

    std::cout << "before set the model" << std::endl;


//    calibrator.setModel(jutzy);

    std::cout << "set the model" << std::endl;

//    calibrator.optimize();

    std::cout << "optimized" << std::endl;


    return 1;
}

int CalibrateDevice::checkSelected()
{
    ccHObject *selected = getSelectedEntityAsCCHObject();
    if (selected && selected->getMetaData("class_name") == "ccCalibrationDB")
        return 1;
    else
        return 0;
}

int CalibrateDevice::openInputDialog()
{

    if (!m_dialog)
        m_dialog = new ccCalibrateDeviceDlg(0);

    /// we need to init the dialog

    return m_dialog->exec() ? 1 : 0;
}
