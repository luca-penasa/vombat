#ifndef CC_CALIBRATION_MODEL_H
#define CC_CALIBRATION_MODEL_H


#include <spc/elements/Attitude.h>

//#include "DistanceComputationTools.h"
#include "ccPointCloud.h"
#include "ccNormalVectors.h"


#include <ccoutofcore/ccMyBaseObject.h>

#include <spc/elements/ICalPHFunction.h>

//#include <boost/serialization/shared_ptr.hpp>

#include <spc/io/element_io.h>

#include <QIcon>




///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological attitude
///
class ccCalibrationModel:  public ccMyBaseObject
{
public:
    ccCalibrationModel();

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/ca.png"));
    }

    //inherited from ccSerializableObject
    virtual bool isSerializable() const
    {
        return true;
    }



    virtual spc::ElementBase::Ptr getSPCElement() const
    {
        return m_attitude;
    }

protected:


    virtual bool toFile_MeOnly(QFile &out) const;
    virtual bool fromFile_MeOnly(QFile &in, short dataVersion, int flags);



    virtual QString getSPCClassName() const
    {
        return "ccCalibrationModel";
    }




    /// the attitude itself
    spc::Attitude::Ptr m_attitude;

};//end class

#endif // CCPLANEORIENTATION_H
