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
		memcpy(m_rgbColor, ccColor::red.rgba, sizeof(colorType) * 3);

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

        if (isSelected())
        {
			glColor3ubv(ccColor::red.rgba);
            glLineWidth(3);
        }
        else
        {
            glLineWidth(2);
			glColor3ubv(ccColor::orange.rgba);
        }
        glPushAttrib(GL_LINE_BIT);

        glLineStipple(2, 0xAAAA);
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






};

#endif // CC_STRATIGRAPHIC_CONSTRAIN_H
