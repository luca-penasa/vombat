#ifndef CC_CALIBRATION_MODEL_H
#define CC_CALIBRATION_MODEL_H


#include <spc/elements/Attitude.h>

//#include "DistanceComputationTools.h"
#include "ccPointCloud.h"
#include "ccNormalVectors.h"


#include <ccoutofcore/ccSPCElementShell.h>

//#include <spc/experimental/ICalPHFunction.h>

//#include <boost/serialization/shared_ptr.hpp>

#include <spc/io/element_io.h>

#include <QIcon>




///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological attitude
///
class ccCalibrationModel:  public ccSPCElementShell
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



protected:


    virtual bool toFile_MeOnly(QFile &out) const;
    virtual bool fromFile_MeOnly(QFile &in, short dataVersion, int flags);





    /// the attitude itself
    spc::Attitude::Ptr m_attitude;

};//end class

#endif // CCPLANEORIENTATION_H
