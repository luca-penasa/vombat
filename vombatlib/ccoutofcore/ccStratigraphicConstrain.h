#ifndef CC_STRATIGRAPHIC_CONSTRAIN_H
#define CC_STRATIGRAPHIC_CONSTRAIN_H


#include <spc/elements/StratigraphicConstrain.h>
#include <ccoutofcore/ccMyBaseObject.h>
#include <ccPolyline.h>
#include <pcl/common/common.h>
#include <pcl/filters/extract_indices.h>
#include <boost/foreach.hpp>


static QSharedPointer<ccSphere> c_unitPointMarker(0);


class ccStratigraphicConstrain: public ccMyBaseObject
{
public:
    ccStratigraphicConstrain()
    {
        QVariant var("Stratigraphic correspondence constrain");
        setMetaData(QString("[vombat][ccStratigraphicConstrain]"), var);

        m_foreground = false;
        m_width  = 0.0;
        memcpy(m_rgbColor, ccColor::red, sizeof(colorType) * 3);

        setVisible(true);
    }

    ccStratigraphicConstrain(spc::StratigraphicConstrain::Ptr sel)
    {
        constrain_ = sel;    }

    virtual bool isSerializable() const override
    { return true; }

    virtual bool hasColors() const override
    { return true; }


    virtual ccBBox getMyOwnBB() override
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
    virtual void drawMeOnly(CC_DRAW_CONTEXT &context) override
    {

        if (!this->constrain_)
            return;

        bool pushName = MACRO_DrawEntityNames(context);
        if (pushName) {
            // not particularily fast
            if (MACRO_DrawFastNamesOnly(context))
                return;
            glPushName(getUniqueIDForDisplay());
        }

//        const float c_sizeFactor = 4.0f;
//        bool loop = false;

//        if (!c_unitPointMarker || c_unitPointMarker->getRadius() != m_radius_) {
//            c_unitPointMarker = QSharedPointer
//                    <ccSphere>(new ccSphere(m_radius_, 0, "PointMarker", 12));
//            c_unitPointMarker->showColors(true);
//            c_unitPointMarker->setVisible(true);
//            c_unitPointMarker->setEnabled(true);


//        }

//        // build-up point maker own 'context'
//        CC_DRAW_CONTEXT markerContext = context;
//        markerContext.flags
//                &= (~CC_DRAW_ENTITY_NAMES); // we must remove the 'push name flag' so
//        // that the sphere doesn't push its own!
//        markerContext._win = 0;

//        if (isSelected() && !pushName)
//            c_unitPointMarker->setTempColor(ccColor::green);
//        else
//            c_unitPointMarker->setTempColor(ccColor::magenta);


//        for (int i =0; i < constrain_->getNumberOfConstrains(); ++i)
//        {

//            Eigen::Vector3f point = constrain_->getPolyLineRep().getPoint(i);

//            glMatrixMode(GL_MODELVIEW);

//            glPushMatrix();

//            ccGL::Translate(point(0), point(1), point(2));
//            glScalef(context.pickedPointsRadius, context.pickedPointsRadius,
//                     context.pickedPointsRadius);

////            m_current_scaling_ = context.pickedPointsRadius;

//            c_unitPointMarker->draw(markerContext);


//            glPopMatrix();

//        }


        if (colorsShown())
            glColor3ubv(m_rgbColor);

        glPushAttrib(GL_LINE_BIT);

        glLineStipple(1, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINE_STRIP);
        for (int i =0; i < constrain_->getNumberOfConstrains(); ++i)
        {
            Eigen::Vector3f point = constrain_->getPolyLineRep().getPoint(i);
            ccGL::Vertex3v(point.data());
        }
        glEnd();


        glPopAttrib();

        if (pushName)
            glPopName();

    }
public:
    void setColor(const colorType col[])
    {
        memcpy(m_rgbColor,col,sizeof(colorType)*3);
    }

    void setWidth(PointCoordinateType width)
    {
        m_width = width;
    }

    const colorType* getColor() const
    {
        return m_rgbColor;
    }

    virtual QString getSPCClassName() const
    {
        return "ccStrtigraphicConstrain";
    }


protected:
    //    virtual void applyGLTransformation(const ccGLMatrix& trans) {}
    //    virtual void setGLTransformation(const ccGLMatrix& trans) {}

    //! Unique RGB color
    colorType m_rgbColor[3];

    //! Width of the line
    PointCoordinateType m_width = 1;
    spc::StratigraphicConstrain::Ptr constrain_;


    int m_radius_ = 1;


    //! Whether poyline should draws itself in background (false) or foreground (true)
    bool m_foreground;


    virtual spc::ElementBase::Ptr getSPCElement() const
    {
        DCHECK(constrain_!=NULL);
        return constrain_;
    }




};

#endif // CC_STRATIGRAPHIC_CONSTRAIN_H
