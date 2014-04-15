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
    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/device.png"));
    }


    spc::CalibrationModelBase::Ptr getModel() const
    {
        return model_;
    }



protected:
    spc::CalibrationModelBase::Ptr model_;

   /* friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(model_);
        ar & boost::serialization::make_nvp("ccMyBaseObject", boost::serialization::base_object<ccMyBaseObject> (*this));
    }*/



    void initMetadata()
    {
        QVariant var("A calibration model");
        setMetaData(QString("[vombat][ccCalibrationModel]"), var);
    }




};

#endif // CCCALIBRATIONMODEL_H
