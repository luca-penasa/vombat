#ifndef CC_GEOLOGIC_PLANE_H
#define CC_GEOLOGIC_PLANE_H


#include <spc/elements/attitude.h>

//#include "DistanceComputationTools.h"
#include "ccPointCloud.h"
#include "ccNormalVectors.h"


#include <ccoutofcore/ccMyBaseObject.h>

#include <boost/serialization/shared_ptr.hpp>



#include <QIcon>




///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological attitude
///
class ccAttitude:  public ccMyBaseObject

{
public:
    ccAttitude(CCVector3 center, CCVector3 orientation);

    ccAttitude(spc::spcAttitude att);

    ccAttitude(spc::spcAttitude::Ptr att_ptr);

    ccAttitude();

    //inherited methods (ccHObject)
    virtual bool hasColors() const { return true; }
    virtual ccBBox getMyOwnBB();

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/attitude.png"));
    }




protected:

    //    void setAttitudeAsMetadata();

    virtual void drawMeOnly(CC_DRAW_CONTEXT &context);
    virtual void applyGLTransformation(const ccGLMatrix& trans);
    virtual void setGLTransformation(const ccGLMatrix& trans);


    void initParameters();
    void initMetadata();

    float m_scale;
    float m_scale_factor;

    int m_width;


    /// the attitude itself
    spc::spcAttitude::Ptr m_attitude;

public:
    spc::spcAttitude::Ptr getAttitude() const
    {
        return m_attitude;
    }

    void setAttitude(spc::spcAttitude::Ptr att)
    {
        m_attitude = att;
    }

    void setAttitude(spc::spcAttitude att)
    {
        spc::spcAttitude::Ptr at_ptr = boost::make_shared<spc::spcAttitude> (att);
        setAttitude(at_ptr);
    }

    //    ccGLMatrix m_oldTransform;

protected:
    static Eigen::Vector3f asEigenVector(CCVector3 v)
    {
        return Eigen::Vector3f (v.x, v.y, v.z); //we should make a MAP instead than a copy!
    }

    static CCVector3 asCCVector(Eigen::Vector3f v)
    {
        return CCVector3(v(0),v(1), v(2));
    }


    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(m_scale);
        ar & BOOST_SERIALIZATION_NVP(m_width);
        ar & BOOST_SERIALIZATION_NVP(m_attitude);
        ar & boost::serialization::make_nvp("ccMyBaseObject", boost::serialization::base_object<ccMyBaseObject> (*this));

    }



};//end class

#endif // CCPLANEORIENTATION_H
