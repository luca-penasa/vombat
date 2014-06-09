#ifndef CCCALIBRATIONMODEL_H
#define CCCALIBRATIONMODEL_H

#include <ccoutofcore/ccMyBaseObject.h>
#include <spc/elements/ICalModelBase.h>

class ccCalibrationModel: public ccMyBaseObject
{
public:
    ///
    /// \brief ccCalibrationModel we can keep here any kind of calibration model for
    /// laserscanning devices
    /// \param mod
    ///
    ccCalibrationModel(spc::CalibrationModelBase::Ptr mod);

    /// for having a nice icon
    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/device.png"));
    }

    virtual spc::ElementBase::Ptr getSPCElement() const
    {
        return model_;
    }


    spc::CalibrationModelBase::Ptr getModel() const
    {
        return model_;
    }

    virtual QString getSPCClassName() const
    {
        return "ccCalibrationModel";
    }



protected:
    spc::CalibrationModelBase::Ptr model_;

};

#endif // CCCALIBRATIONMODEL_H
