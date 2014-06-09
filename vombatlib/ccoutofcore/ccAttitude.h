#ifndef CC_ATTITUDE_H
#define CC_ATTITUDE_H


#include <spc/elements/Attitude.h>

//#include "DistanceComputationTools.h"
#include "ccPointCloud.h"
#include "ccNormalVectors.h"


#include <ccoutofcore/ccMyBaseObject.h>

//#include <boost/serialization/shared_ptr.hpp>

#include <spc/io/element_io.h>

#include <QIcon>




///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological attitude
///
class ccAttitude:  public ccMyBaseObject
{
public:
    ccAttitude(CCVector3 center, CCVector3 orientation);

    ccAttitude(spc::Attitude att);

    ccAttitude(spc::Attitude::Ptr att_ptr);

    ccAttitude();

    ccAttitude(QString name);

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
        std::cout << "CALLED IF SERIALIZABLE" << std::endl;
        return true;
    }
//    virtual bool toFile(QFile& out) const;
//    virtual bool fromFile(QFile& in, short dataVersion, int flags);



protected:

    //    void setAttitudeAsMetadata();

    virtual void drawMeOnly(CC_DRAW_CONTEXT &context);
    virtual void applyGLTransformation(const ccGLMatrix& trans);
    virtual void setGLTransformation(const ccGLMatrix& trans);


    void initParameters();

    virtual QString getSPCClassName() const
    {
        return "ccAttitude";
    }

    float m_scale;
    float m_scale_factor;

    int m_width;


    /// the attitude itself
    spc::Attitude::Ptr m_attitude;

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

    virtual spc::ElementBase::Ptr getSPCElement() const
    {
        return m_attitude;
    }


protected:
    static Eigen::Vector3f asEigenVector(CCVector3 v)
    {
        return Eigen::Vector3f (v.x, v.y, v.z); //we should make a MAP instead than a copy!
    }

    static CCVector3 asCCVector(Eigen::Vector3f v)
    {
        return CCVector3(v(0),v(1), v(2));
    }




    // ccHObject interface
protected:
    virtual bool toFile_MeOnly(QFile &out) const;
    virtual bool fromFile_MeOnly(QFile &in, short dataVersion, int flags);


};//end class

#endif // CCPLANEORIENTATION_H
