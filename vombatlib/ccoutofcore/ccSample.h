#pragma once
#ifndef CCSAMPLE_H
#define CCSAMPLE_H

#include <ccSPCElementShell.h>
#include <spc/elements/Sample.h>
#include <cc2DLabel.h>
#include <ccGenericPointCloud.h>

#include <ccSphere.h>
#include <ccInteractor.h>
#include <helpers/ccSPCObjectsStreamer.h>

class ccSample : public ccSPCElementShell, public ccInteractor
{

    typedef spc::Sample SPCType;
    typedef spc::Sample::Ptr SPCPtrType;
public:



    ccSample(): m_radius_(1), ccSPCElementShell(SPCPtrType(new SPCType(0,0,0)))
    {        
        m_selectionBehavior = SELECTION_IGNORED;
    }


    ccSample(const spc::Point3D point):
        ccSPCElementShell(SPCPtrType(new SPCType(point.getPosition())), point.getElementName().c_str())
    {        
        m_selectionBehavior = SELECTION_IGNORED;
    }

    ccSample(SPCPtrType sample): ccSPCElementShell(sample)
    {
        m_selectionBehavior = SELECTION_IGNORED;
    }

    ccSample(const cc2DLabel *label): m_radius_(1),
        ccSPCElementShell(SPCPtrType( new SPCType), label->getName())
    {



        cc2DLabel::PickedPoint picked_point
            = label->getPoint(0); // we only use 0-point
        CCVector3 point;
        picked_point.cloud->getPoint(picked_point.index, point);

       getSample()->setPosition(Eigen::Vector3f(point.x, point.y, point.z));

        m_selectionBehavior = SELECTION_IGNORED;

    }

    ccSample(const CCVector3 &v): m_radius_(1), ccSPCElementShell(SPCPtrType(new spc::Sample(v.x, v.y, v.z)))
    {
        m_selectionBehavior = SELECTION_IGNORED;

    }



//    virtual ccBBox getMyOwnBB();

    virtual QIcon getIcon() const
    {
        if (getSample()->getManual())
            return QIcon(QString::fromUtf8(":/toolbar/icons/sample.png"));
        else
            return QIcon(QString::fromUtf8(":/toolbar/icons/sample_locked.png"));
    }

    virtual bool hasColors() const
    {
        return true;
    }

    SPCType::Ptr getSample() const
    {
        return getSPCElement<SPCType>();
    }


    ccBBox getMyOwnBB()
    {
        CCVector3 center = CCVector3::fromArray (getSample()->getPosition().data());
        float s = 0.1; //10 cm

        CCVector3 scale_v (s,s,s);
        CCVector3 min_corner(center - scale_v);
        CCVector3 max_corner(center + scale_v);
        ccBBox box(min_corner, max_corner);

        return box;
    }


    void drawStratPos(CC_DRAW_CONTEXT &context);
protected:
    virtual void drawMeOnly(CC_DRAW_CONTEXT &context);

//    spc::Sample::Ptr m_sample;

protected:
    virtual bool toFile_MeOnly(QFile &out) const
    {
        ccSPCElementShell::toFile_MeOnly(out);
        ccSPCObjectsStreamer::WriteToQFile(getSPCElement(), out);
        return true;
    }
    virtual bool fromFile_MeOnly(QFile &in, short dataVersion, int flags)
    {
        ccSPCElementShell::fromFile_MeOnly(in, dataVersion, flags);
        return true;
    }

    int m_radius_ = 1;
    float m_current_scaling_;

};

#endif // CCSAMPLE_H
