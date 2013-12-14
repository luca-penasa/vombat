#ifndef CCCALIBRATIONMODEL_H
#define CCCALIBRATIONMODEL_H

#include <ccoutofcore/ccMyBaseObject.h>
#include <spc/devices/calibration_model_base.h>

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
    virtual QIcon * getIcon() const;


protected:
    spc::CalibrationModelBase::Ptr model_;



    void initMetadata()
    {
        QVariant var("A calibration model");
        setMetaData(QString("[vombat][ccCalibrationModel]"), var);
    }




};

#endif // CCCALIBRATIONMODEL_H
