#pragma once
#ifndef CC_STRATIGRAPHIC_CONSTRAIN_H
#define CC_STRATIGRAPHIC_CONSTRAIN_H

#include <ccoutofcore/ccSPCElementShell.h>

namespace spc
{
spcFwdDeclSharedPtr(StratigraphicConstrain)
}


class ccStratigraphicConstrain : public ccSPCElementShell {
public:
    ccStratigraphicConstrain();

    ccStratigraphicConstrain(spc::StratigraphicConstrainPtr sel);
    ~ccStratigraphicConstrain();

    virtual bool isSerializable() const override
    {
        return true;
    }

    virtual bool hasColors() const override
    {
        return true;
    }

    virtual ccBBox getOwnBB(bool withGLFeatures = false) override;

    virtual QIcon getIcon() const override;

protected:
    virtual void drawMeOnly(CC_DRAW_CONTEXT& context) override;

public:
    void setColor(const ccColor::Rgb& col)
    {
        m_rgbColor = col;
    }

    void setWidth(PointCoordinateType width)
    {
        m_width = width;
    }

    const ccColor::Rgb getColor() const
    {
        return m_rgbColor;
    }

protected:
    //    virtual void applyGLTransformation(const ccGLMatrix& trans) {}
    //    virtual void setGLTransformation(const ccGLMatrix& trans) {}

    //! Unique RGB color
    ccColor::Rgb m_rgbColor;

    //! Width of the line
    PointCoordinateType m_width = 1;
//    spc::StratigraphicConstrainPtr constrain_;

    int m_radius_ = 1;

    //! Whether poyline should draws itself in background (false) or foreground (true)
    bool m_foreground;
};

#endif // CC_STRATIGRAPHIC_CONSTRAIN_H
