#pragma once
#ifndef CC_CALIBRATION_MODEL_H
#define CC_CALIBRATION_MODEL_H

#include <ccoutofcore/ccSPCElementShell.h>

namespace spc {
spcFwdDeclSharedPtr(Attitude)
}

///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological attitude
///
class ccCalibrationModel : public ccSPCElementShell {
public:
    ccCalibrationModel();

    virtual QIcon getIcon() const;

    //inherited from ccSerializableObject
    virtual bool isSerializable() const
    {
        return true;
    }

protected:
    virtual bool toFile_MeOnly(QFile& out) const;
    virtual bool fromFile_MeOnly(QFile& in, short dataVersion, int flags);

    /// the attitude itself
    spc::AttitudePtr m_attitude;

}; //end class

#endif // CCPLANEORIENTATION_H
