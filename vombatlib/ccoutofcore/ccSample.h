#pragma onces
#ifndef CCSAMPLE_H
#define CCSAMPLE_H

#include <ccMyBaseObject.h>
#include <spc/elements/Sample.h>
#include <cc2DLabel.h>
#include <ccGenericPointCloud.h>

#include <ccSphere.h>
#include <ccInteractor.h>

class ccSample: public ccMyBaseObject
{
public:
    ccSample()
    {
        m_sample = spc::Sample::Ptr(new spc::Sample(0.0,0.0,0.0));
    }
    ccSample(const cc2DLabel * label)
    {
        m_sample = spc::Sample::Ptr(new spc::Sample);

        cc2DLabel::PickedPoint picked_point = label->getPoint(0); //we only use 0-point
        CCVector3 point;
        picked_point.cloud->getPoint(picked_point.index, point);

        this->m_sample->setPosition(Eigen::Vector3f(point.x,point.y,point.z));
    }

    //    virtual bool acceptClick(int x, int y, Qt::MouseButton button)
    //    {
    //        //do nothing
    //    }

    virtual ccBBox getMyOwnBB()
    {
        CCVector3 center = CCVector3 (m_sample->getPosition().data());
        float s = 0.5;
        CCVector3 scale_v (s,s,s);
        CCVector3 min_corner(center - scale_v);
        CCVector3 max_corner(center + scale_v);
        ccBBox box(min_corner, max_corner);

        return box;
    }

    ccSample(const CCVector3 & v)
    {
        m_sample = spc::Sample::Ptr(new spc::Sample(v.x, v.y, v.z));
    }

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/sample.png"));
    }

    virtual bool hasColors() const { return false; }


protected:

    virtual void drawMeOnly(CC_DRAW_CONTEXT &context);


    spc::Sample::Ptr m_sample;


};

#endif // CCSAMPLE_H
