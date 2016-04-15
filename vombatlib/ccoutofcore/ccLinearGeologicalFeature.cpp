#include "ccLinearGeologicalFeature.h"
#include <spc/elements/LinearGeologicalFeature.h>
#include <vombat.h>
#include <ccSphere.h>
#include <ccPolyline.h>

#include <ccGenericGLDisplay.h>

static QSharedPointer<ccSphere> c_unitPointMarker(0);


ccLinearGeologicalFeature::ccLinearGeologicalFeature()
    : ccStratigraphicPositionableElement(spc::LinearGeologicalFeature::Ptr(new spc::LinearGeologicalFeature))
{

//    constrain_ = this->getSPCElement<spc::LinearGeologicalFeature>();

    m_foreground = false;
    m_width = 0.0;
    //		memcpy(m_rgbColor, ccColor::red.rgba, sizeof(colorType) * 3);
    m_rgbColor = ccColor::red;
    setVisible(true);
}

ccLinearGeologicalFeature::ccLinearGeologicalFeature(LinearGeologicalFeature::Ptr sel)
    : ccStratigraphicPositionableElement(sel)
{
    m_selectionBehavior = SELECTION_IGNORED;

//    constrain_ = sel;
}

ccLinearGeologicalFeature::~ccLinearGeologicalFeature()
{

}

ccBBox ccLinearGeologicalFeature::getOwnBB(bool withGLFeatures)
{
//    CHECK(constrain_ != NULL);

    spc::BoundingBox<float, 3> bb = this->getSPCElement<spc::LinearGeologicalFeature>()->getPolyline().getBB();

    CCVector3 min(bb.min_.data());
    CCVector3 max(bb.max_.data());

    return ccBBox(min, max);
}

QIcon ccLinearGeologicalFeature::getIcon() const
{
    return QIcon(QString::fromUtf8(":/toolbar/icons/linear_geological_feature.png"));
}

ccLinearGeologicalFeature *ccLinearGeologicalFeature::fromPolyline(const ccPolyline &pline)
{
   return fromPointCloud(*pline.getAssociatedCloud());
}

ccLinearGeologicalFeature *ccLinearGeologicalFeature::fromPointCloud(const CCLib::GenericIndexedCloudPersist &pline)
{
    ccLinearGeologicalFeature * linear = new ccLinearGeologicalFeature;

    spc::LinearGeologicalFeature::Ptr asspc =  linear->getSPCElement<spc::LinearGeologicalFeature>();
    for (int i = 0; i < pline.size() ; ++i)
    {
        CCVector3 p;
        pline.getPoint(i, p);

        Eigen::Map<Eigen::Vector3f> mapped (&p[0]);

        asspc->getPolyline().addPoint(mapped);
    }

    return linear;
}


void ccLinearGeologicalFeature::drawStratPos(CC_DRAW_CONTEXT& context)
{
    QFont font(context._win->getTextDisplayFont()); // takes rendering zoom into
    // account!
    font.setPointSize(font.pointSize());
    font.setBold(true);

    //    // draw their name
    //	glPushAttrib(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    float sp = getSPCElement<spc::LinearGeologicalFeature>()->getStratigraphicPosition();
//    LOG(INFO) << sp;
    QString name = QString::number(sp, 'g', 3);

    context._win->display3DLabel(name,
        CCVector3(getSPCElement<spc::LinearGeologicalFeature>()->getPolyline().getPoint(0).data()),
        ccColor::red.rgba, font);

    glEnable(GL_DEPTH_TEST);
}





void ccLinearGeologicalFeature::drawMeOnly(CC_DRAW_CONTEXT& context)
{

    if (!this->getSPCElement<spc::LinearGeologicalFeature>())
        return;

    if (getSPCElement<spc::LinearGeologicalFeature>()->getPolyline().getNumberOfPoints() ==0)
        return;

    if (MACRO_Draw3D(context)) {

        QOpenGLFunctions_2_1 *glFunc = context.glFunctions<QOpenGLFunctions_2_1>();
        assert( glFunc != nullptr );

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

        glPushAttrib(GL_LINE_BIT);

        if (isSelected()) {
            glColor3ubv(ccColor::red.rgba);
            glLineWidth(5);
//            glLineStipple(5, 0xAAAA);
        }
        else {
            glLineWidth(2);
            glColor3ubv(ccColor::orange.rgba);
//            glLineStipple(2, 0xAAAA);
        }

//        glEnable(GL_LINE_STIPPLE);

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < this->getSPCElement<spc::LinearGeologicalFeature>()->getPolyline().getNumberOfPoints(); ++i) {
            Eigen::Vector3f point = this->getSPCElement<spc::LinearGeologicalFeature>()->getPolyline().getPoint(i);
            ccGL::Vertex3v(glFunc, point.data());
        }
        glEnd();

        drawStratPos(context);

        glPopAttrib();

        if (pushName)
            glPopName();
    }
}
