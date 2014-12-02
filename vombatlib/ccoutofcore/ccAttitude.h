#ifndef CC_ATTITUDE_H
#define CC_ATTITUDE_H


#include <spc/elements/Attitude.h>

//#include "DistanceComputationTools.h"
#include "ccPointCloud.h"
#include "ccNormalVectors.h"


#include <ccoutofcore/ccSPCElementShell.h>

//#include <boost/serialization/shared_ptr.hpp>

#include <spc/io/element_io.h>

#include <QIcon>




///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological attitude
///
class ccAttitude:  public ccSPCElementShell
{
public:
    ccAttitude(): m_attitude(new spc::Attitude), ccSPCElementShell(m_attitude)
    {
        m_selectionBehavior = SELECTION_IGNORED;


    }

    ccAttitude(CCVector3 center, CCVector3 orientation);

    ccAttitude(spc::Attitude att);

    ccAttitude(spc::Attitude::Ptr att_ptr);

    void flipNormal();

    //inherited methods (ccHObject)
    virtual bool hasColors() const { return true; }
    virtual ccBBox getMyOwnBB();

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/attitude.png"));
    }

    //inherited from ccSerializableObject
    virtual bool isSerializable() const
    {
        return true;
    }

public:
    spc::Attitude::Ptr getAttitude() const
    {
        return m_attitude;
    }

    void setAttitude(spc::Attitude::Ptr att)
    {
        m_attitude = att;
    }

    void setAttitude(spc::Attitude att)
    {
        spc::Attitude::Ptr at_ptr = spcMakeSharedPtrMacro<spc::Attitude> (att);
        setAttitude(at_ptr);
    }



protected:
    static Eigen::Vector3f asEigenVector(CCVector3 v)
    {
        return Eigen::Vector3f (v.x, v.y, v.z);
    }

    static CCVector3 asCCVector(Eigen::Vector3f v)
    {
        return CCVector3(v(0),v(1), v(2));
    }

    virtual bool toFile_MeOnly(QFile &out) const;
    virtual bool fromFile_MeOnly(QFile &in, short dataVersion, int flags);


    virtual void drawMeOnly(CC_DRAW_CONTEXT &context);

    float m_scale = 10;
    int m_width = 4;


    /// the attitude itself
    spc::Attitude::Ptr m_attitude;

};//end class

#endif // CCPLANEORIENTATION_H
