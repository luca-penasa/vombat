#ifndef CC_STRATIGRAPHIC_CONSTRAIN_H
#define CC_STRATIGRAPHIC_CONSTRAIN_H


#include <spc/elements/StratigraphicConstrain.h>
#include <ccoutofcore/ccSPCElementShell.h>
#include <ccPolyline.h>
#include <pcl/common/common.h>
#include <pcl/filters/extract_indices.h>
#include <boost/foreach.hpp>
#include <ccSphere.h>


static QSharedPointer<ccSphere> c_unitPointMarker(0);


class ccStratigraphicConstrain: public ccSPCElementShell
{
public:
    ccStratigraphicConstrain(): ccSPCElementShell(spc::StratigraphicConstrain::Ptr(new spc::StratigraphicConstrain))
    {

        constrain_ = this->getSPCElement<spc::StratigraphicConstrain>();


        m_foreground = false;
        m_width  = 0.0;
//		memcpy(m_rgbColor, ccColor::red.rgba, sizeof(colorType) * 3);
        m_rgbColor = ccColor::red;
        setVisible(true);
    }

    ccStratigraphicConstrain(spc::StratigraphicConstrain::Ptr sel): ccSPCElementShell(sel)
    {
        m_selectionBehavior = SELECTION_IGNORED;

        constrain_ = sel;
    }
    ~ccStratigraphicConstrain()
    {
        for (spc::ElementBase::Ptr el: constrain_->getVertices())
        {
            ccHObject * ob = vombat::theInstance()->getObjectFromElement(el);
            if(ob) //! < maybe has been deleted in the meanwhile \todo this should not happen but it does check why
                ob->setLocked(false);
        }
    }

    virtual bool isSerializable() const override
    { return true; }

    virtual bool hasColors() const override
    { return true; }


	virtual ccBBox getOwnBB(bool withGLFeatures = false) override
    {
        CHECK(constrain_ != NULL);


        spc::BoundingBox<float, 3> bb= constrain_->getPolyLineRep().getBB();

        CCVector3 min (bb.min_.data());
        CCVector3 max (bb.max_.data());

        return ccBBox(min, max);
    }


    virtual QIcon getIcon() const override
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/stratigraphic_constrain.png"));
    }

protected:
	virtual void drawMeOnly(CC_DRAW_CONTEXT &context) override;
public:
    void setColor(const ccColor::Rgb &col)
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
    spc::StratigraphicConstrain::Ptr constrain_;




    int m_radius_ = 1;


    //! Whether poyline should draws itself in background (false) or foreground (true)
    bool m_foreground;






};

#endif // CC_STRATIGRAPHIC_CONSTRAIN_H
