#pragma once
#ifndef CCPLANARSELECTION_H
#define CCPLANARSELECTION_H


#include <ccoutofcore/ccSPCElementShell.h>


namespace spc
{
spcFwdDeclSharedPtr(SelectionRubberband)
}

class ccPlanarSelection: public ccSPCElementShell
{
public:
    ccPlanarSelection();

    ccPlanarSelection(spc::SelectionRubberbandPtr sel);

    virtual bool isSerializable() const override
    { return true; }

    virtual bool hasColors() const override
    { return true; }


//    virtual ccBBox getMyOwnBB() override;

	virtual ccBBox getOwnBB(bool withGLFeatures = false) override;


    virtual QIcon getIcon() const override;

protected:
    virtual void drawMeOnly(CC_DRAW_CONTEXT &context) override;
public:
    void setColor(const ccColor::Rgb & col)
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

    spc::SelectionRubberbandPtr getRubberband() const;




protected:
    //    virtual void applyGLTransformation(const ccGLMatrix& trans) {}
    //    virtual void setGLTransformation(const ccGLMatrix& trans) {}

    //! Unique RGB color
//    colorType m_rgbColor[3];

    ccColor::Rgb m_rgbColor;

    //! Width of the line
    PointCoordinateType m_width = 2;
//    spc::SelectionRubberband::Ptr getRubberband();


    //! Whether poyline should draws itself in background (false) or foreground (true)
    bool m_foreground;





};

#endif // CCPLANARSELECTION_H
