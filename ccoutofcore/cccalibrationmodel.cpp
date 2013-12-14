#include "cccalibrationmodel.h"


ccCalibrationModel::ccCalibrationModel(spc::CalibrationModelBase::Ptr mod)
{
    model_ = mod;
    initMetadata();
}

QIcon *ccCalibrationModel::getIcon() const
{
    return new QIcon(QString::fromUtf8(":/toolbar/icons/device.png"));
}
