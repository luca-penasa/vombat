#pragma once
#ifndef CCSAMPLE_H
#define CCSAMPLE_H

//#include <spc/elements/Sample.h>
//#include <cc2DLabel.h>
//#include <ccGenericPointCloud.h>

//#include <ccSphere.h>
#include <spc/core/macros.h>

#include <ccSPCElementShell.h>
#include <ccInteractor.h>

//#include <helpers/ccSPCObjectsStreamer.h>
namespace spc {
spcFwdDeclSharedPtr(Point3D)
    spcFwdDeclSharedPtr(Sample)
}

class cc2DLabel;

class ccSample : public ccSPCElementShell, public ccInteractor
{
    Q_OBJECT

public:

    Q_PROPERTY(double Radius READ getRadius WRITE setRadius)
    Q_PROPERTY(bool Manual READ getManual WRITE setManual)
    Q_PROPERTY(double StratigraphicPosition READ getStratigraphicPosition WRITE setStratigraphicPosition)



    ccSample();

    ccSample(const spc::Point3D& point);

    ccSample(const spc::SamplePtr sample);

    ccSample(const cc2DLabel* label);

    ccSample(const CCVector3& v);

    virtual QIcon getIcon() const;

    spcSetMacro(Radius, m_radius_, float)
    spcGetMacro(Radius, m_radius_, float)

    double getStratigraphicPosition();

    void setStratigraphicPosition( const double sp);


    void setManual(const bool status);

    bool getManual();

    virtual bool hasColors() const
    {
        return true;
    }

    spc::SamplePtr getSample() const;

    ccBBox getMyOwnBB();

    void drawStratPos(CC_DRAW_CONTEXT& context);

protected:
    virtual void drawMeOnly(CC_DRAW_CONTEXT& context);

    //    spc::Sample::Ptr m_sample;

protected:
    //    virtual bool toFile_MeOnly(QFile& out) const;
    //    virtual bool fromFile_MeOnly(QFile& in, short dataVersion, int flags);

    double m_radius_ = 1;
    float m_current_scaling_;
};

#endif // CCSAMPLE_H
