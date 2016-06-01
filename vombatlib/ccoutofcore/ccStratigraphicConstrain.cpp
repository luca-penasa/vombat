#include "ccStratigraphicConstrain.h"
#include <spc/elements/StratigraphicConstrain.h>
#include <vombat.h>
#include <ccSphere.h>

static QSharedPointer<ccSphere> c_unitPointMarker(0);


ccStratigraphicConstrain::ccStratigraphicConstrain()
    : ccSPCElementShell(spc::StratigraphicConstrain::Ptr(new spc::StratigraphicConstrain))
{

//    constrain_ = this->getSPCElement<spc::StratigraphicConstrain>();

    m_foreground = false;
    m_width = 0.0;
    //		memcpy(m_rgbColor, ccColor::red.rgba, sizeof(colorType) * 3);
    m_rgbColor = ccColor::red;
    setVisible(true);
}

ccStratigraphicConstrain::ccStratigraphicConstrain(StratigraphicConstrain::Ptr sel)
    : ccSPCElementShell(sel)
{
    m_selectionBehavior = SELECTION_IGNORED;

//    constrain_ = sel;
}

ccStratigraphicConstrain::~ccStratigraphicConstrain()
{
    for (spc::ElementBase::Ptr el : this->getSPCElement<spc::StratigraphicConstrain>()->getVertices()) {
        ccHObject* ob = vombat::theInstance()->getObjectFromElement(el);
        if (ob) //! < maybe has been deleted in the meanwhile \todo this should not happen but it does check why
            ob->setLocked(false);
    }
}

ccBBox ccStratigraphicConstrain::getOwnBB(bool withGLFeatures)
{
//    CHECK(constrain_ != NULL);

    spc::BoundingBox<float, 3> bb = this->getSPCElement<spc::StratigraphicConstrain>()->getPolyLineRep().getBB();

    CCVector3 min(bb.min_.data());
    CCVector3 max(bb.max_.data());

    return ccBBox(min, max);
}

QIcon ccStratigraphicConstrain::getIcon() const
{
    return QIcon(QString::fromUtf8(":/toolbar/icons/stratigraphic_constrain.png"));
}

void ccStratigraphicConstrain::drawMeOnly(CC_DRAW_CONTEXT& context)
{

    if (!this->getSPCElement<spc::StratigraphicConstrain>())
        return;

    if (MACRO_Draw3D(context)) {
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
        //        markercontext.display = 0;

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

        glPushAttrib(GL_LINE_BIT);

        if (isSelected()) {
            glColor3ubv(ccColor::red.rgba);
            glLineWidth(5);
            glLineStipple(5, 0xAAAA);
        }
        else {
            glLineWidth(2);
            glColor3ubv(ccColor::orange.rgba);
            glLineStipple(2, 0xAAAA);
        }

        glEnable(GL_LINE_STIPPLE);

        QOpenGLFunctions_2_1 *glFunc = context.glFunctions<QOpenGLFunctions_2_1>();
        assert( glFunc != nullptr );

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < this->getSPCElement<spc::StratigraphicConstrain>()->getNumberOfConstrains(); ++i) {
            Eigen::Vector3f point = this->getSPCElement<spc::StratigraphicConstrain>()->getPolyLineRep().getPoint(i);
//            ccGL::Vertex3v(glFunc, );

            glFunc->glVertex3fv(point.data());
        }
        glEnd();

        glPopAttrib();

        if (pushName)
            glPopName();
    }
}
