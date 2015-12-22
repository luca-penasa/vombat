#pragma once
#ifndef CC_ATTITUDE_H
#define CC_ATTITUDE_H

#include <ccoutofcore/ccSPCElementShell.h>
#include <spc/core/spc_eigen.h>

namespace spc {
spcFwdDeclSharedPtr(Attitude)
}

///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological attitude
///
class ccAttitude : public ccSPCElementShell {
public:
    ccAttitude();

    ccAttitude(CCVector3 center, CCVector3 orientation);

    ccAttitude(const spc::Attitude& att);

    ccAttitude(spc::AttitudePtr att_ptr);

    void flipNormal();

    //inherited methods (ccHObject)
    virtual bool hasColors() const { return true; }
    virtual ccBBox getOwnBB();

    virtual QIcon getIcon() const;

    //inherited from ccSerializableObject
    virtual bool isSerializable() const
    {
        return true;
    }

public:
    spc::AttitudePtr getAttitude() const
    {
        return m_attitude;
    }

    void setAttitude(spc::AttitudePtr att)
    {
        m_attitude = att;
    }

    void setAttitude(const spc::Attitude& att);

protected:
    static Eigen::Vector3f asEigenVector(CCVector3 v)
    {
        return Eigen::Vector3f(v.x, v.y, v.z);
    }

    static CCVector3 asCCVector(Eigen::Vector3f v)
    {
        return CCVector3(v(0), v(1), v(2));
    }

    virtual bool toFile_MeOnly(QFile& out) const;
    virtual bool fromFile_MeOnly(QFile& in, short dataVersion, int flags);

    virtual void drawMeOnly(CC_DRAW_CONTEXT& context);

    float m_scale = 10;
    int m_width = 4;

    /// the attitude itself
    spc::AttitudePtr m_attitude;

}; //end class

#endif // CCPLANEORIENTATION_H
