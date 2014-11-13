#pragma once
#ifndef CCSAMPLE_H
#define CCSAMPLE_H

#include <ccMyBaseObject.h>
#include <spc/elements/Sample.h>
#include <cc2DLabel.h>
#include <ccGenericPointCloud.h>

#include <ccSphere.h>
#include <ccInteractor.h>
#include <helpers/ccSPCObjectsStreamer.h>

class ccSample : public ccMyBaseObject, public ccInteractor
{
public:
    ccSample(): m_radius_(1)
    {
        m_sample = spc::Sample::Ptr(new spc::Sample(0.0, 0.0, 0.0));
        writeSPCClassNameToMetadata();
    }


    ccSample(const spc::Point3D::Ptr point)
    {
        m_sample = spcDynamicPointerCast<spc::Sample> (point);
        writeSPCClassNameToMetadata();
    }

    ccSample(const cc2DLabel *label): m_radius_(1)
    {
        m_sample = spc::Sample::Ptr(new spc::Sample);

        cc2DLabel::PickedPoint picked_point
            = label->getPoint(0); // we only use 0-point
        CCVector3 point;
        picked_point.cloud->getPoint(picked_point.index, point);

        this->m_sample->setPosition(Eigen::Vector3f(point.x, point.y, point.z));
        writeSPCClassNameToMetadata();
    }

    ccSample(const CCVector3 &v): m_radius_(1)
    {
        m_sample = spc::Sample::Ptr(new spc::Sample(v.x, v.y, v.z));
        writeSPCClassNameToMetadata();
    }

    ccSample(const spc::Sample::Ptr s): m_radius_(1)
    {
        m_sample = s;
        writeSPCClassNameToMetadata();
    }

//    virtual ccBBox getMyOwnBB();

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/sample.png"));
    }

    virtual bool hasColors() const
    {
        return true;
    }

    virtual QString getSPCClassName() const
    {
        return "ccSample";
    }

    spc::Sample::Ptr getSample() const
    {
        return m_sample;
    }

    virtual spc::ElementBase::Ptr getSPCElement() const
    {
        return m_sample;
    }

protected:
    virtual void drawMeOnly(CC_DRAW_CONTEXT &context);

    spc::Sample::Ptr m_sample;

protected:
    virtual bool toFile_MeOnly(QFile &out) const
    {
        ccCustomHObject::toFile_MeOnly(out);
        ccSPCObjectsStreamer::WriteToQFile(m_sample, out);
        return true;
    }
    virtual bool fromFile_MeOnly(QFile &in, short dataVersion, int flags)
    {
        ccCustomHObject::fromFile_MeOnly(in, dataVersion, flags);
        spc::ISerializable::Ptr el = ccSPCObjectsStreamer::ReadFromQFile(in);
        m_sample = spcDynamicPointerCast<spc::Sample>(el);
        return true;
    }

    int m_radius_;
    float m_current_scaling_;

};

#endif // CCSAMPLE_H
