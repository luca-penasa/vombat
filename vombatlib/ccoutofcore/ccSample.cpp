#include "ccSample.h"
#include <ccGenericGLDisplay.h>
#include <ccSphere.h>
#include <spc/elements/Sample.h>
#include <cc2DLabel.h>
#include <ccGenericPointCloud.h>
// unit point marker

static QSharedPointer<ccSphere> c_unitPointMarker(0);

//ccBBox ccSample::getMyOwnBB()
//{
//    std::cout << "called" << std::endl;

//    CCVector3 center = CCVector3(m_sample->getPosition().data());
//    float s = m_current_scaling_;
//    CCVector3 scale_v(s, s, s);
//    CCVector3 min_corner(center - scale_v);
//    CCVector3 max_corner(center + scale_v);
//    ccBBox box(min_corner, max_corner);

//    return box;
//}

void ccSample::drawStratPos(CC_DRAW_CONTEXT& context)
{
    if (MACRO_Draw3D(context)) {

        QOpenGLFunctions_2_1* glFunc = context.glFunctions<QOpenGLFunctions_2_1>();
        assert(glFunc != nullptr);

        QFont font(context._win->getTextDisplayFont()); // takes rendering zoom into
        // account!
        font.setPointSize(font.pointSize());
        font.setBold(true);

        //    // draw their name
        //	glPushAttrib(GL_DEPTH_BUFFER_BIT);
        glFunc->glDisable(GL_DEPTH_TEST);

        QString name = QString::number(getSample()->getStratigraphicPosition(), 'g', 3);



        context._win->display3DLabel(name,
            CCVector3(getSample()->getPosition().data()),
            ccColor::red.rgba, font);

        //    CCVector3 p (x,y,z);
        //    QString title = (getName());
        //    context._win->display3DLabel(	title,
        //                                    p + CCVector3(
        // context.pickedPointsTextShift,
        //                                                    context.pickedPointsTextShift,
        //                                                    context.pickedPointsTextShift),
        //                                    ccColor::magenta,
        //                                    font );

        //	glPopAttrib();

        glFunc->glEnable(GL_DEPTH_TEST);
    }
}

void ccSample::drawMeOnly(CC_DRAW_CONTEXT& context)
{

    if (MACRO_Draw3D(context)) {
        if (!this->getSample())
            return;

        QOpenGLFunctions_2_1* glFunc = context.glFunctions<QOpenGLFunctions_2_1>();
        assert(glFunc != nullptr);

        bool pushName = MACRO_DrawEntityNames(context);
        if (pushName) {
            // not particularily fast
            if (MACRO_DrawFastNamesOnly(context))
                return;
            glFunc->glPushName(getUniqueIDForDisplay());
        }

        if (!c_unitPointMarker) {
            c_unitPointMarker = QSharedPointer<ccSphere>(new ccSphere(m_radius_, 0, "PointMarker", 12));
            c_unitPointMarker->showColors(true);
            c_unitPointMarker->setVisible(true);
            c_unitPointMarker->setEnabled(true);
        }

        // build-up point maker own 'context'
        CC_DRAW_CONTEXT markerContext = context;
        markerContext.flags
            &= (~CC_DRAW_ENTITY_NAMES); // we must remove the 'push name flag' so
        // that the sphere doesn't push its own!
        markerContext._win = 0;

        if (isSelected() && !pushName) {
            c_unitPointMarker->setTempColor(ccColor::red);
            c_unitPointMarker->setRadius(2 * m_radius_);
        }
        else {
            c_unitPointMarker->setTempColor(ccColor::magenta);
            c_unitPointMarker->setRadius(m_radius_);
        }

        glFunc->glMatrixMode(GL_MODELVIEW);
        glFunc->glPushMatrix();

        float x, y, z;
        Eigen::Vector3f p = this->getSample()->getPosition();
        //    const CCVector3* P = m_points[i].cloud->getPoint(m_points[i].index);
        //        ccGL::Translate();

        glFunc->glTranslatef(p(0), p(1), p(2));

        glFunc->glScalef(context.labelMarkerSize, context.labelMarkerSize,
            context.labelMarkerSize);

        m_current_scaling_ = context.labelMarkerSize;

        c_unitPointMarker->draw(markerContext);

        glFunc->glPopMatrix();

        drawStratPos(context);

        if (pushName)
            glFunc->glPopName();
    }
}

//bool ccSample::toFile_MeOnly(QFile &out) const
//{
//    ccSPCElementShell::toFile_MeOnly(out);
//    ccSPCObjectsStreamer::WriteToQFile(getSPCElement(), out);
//    return true;
//}

//bool ccSample::fromFile_MeOnly(QFile &in, short dataVersion, int flags)
//{
//    ccSPCElementShell::fromFile_MeOnly(in, dataVersion, flags);
//    return true;
//}

ccSample::ccSample()
    : m_radius_(1)
    , ccStratigraphicPositionableElement(spc::Sample::Ptr(new spc::Sample(0, 0, 0)))
{
    m_selectionBehavior = SELECTION_IGNORED;
}

ccSample::ccSample(const spc::Point3D& point)
    : ccStratigraphicPositionableElement(spc::Sample::Ptr(new spc::Sample(point.getPosition())), point.getElementName().c_str())
{
    m_selectionBehavior = SELECTION_IGNORED;
}

ccSample::ccSample(const spc::Sample::Ptr sample)
    : ccStratigraphicPositionableElement(sample)
{
    m_selectionBehavior = SELECTION_IGNORED;
}

ccSample::ccSample(const cc2DLabel* label)
    : m_radius_(1)
    , ccStratigraphicPositionableElement(spc::Sample::Ptr(new spc::Sample), label->getName())
{

    cc2DLabel::PickedPoint picked_point
        = label->getPoint(0); // we only use 0-point
    CCVector3 point;
    picked_point.cloud->getPoint(picked_point.index, point);

    getSample()->setPosition(Eigen::Vector3f(point.x, point.y, point.z));

    m_selectionBehavior = SELECTION_IGNORED;
}

ccSample::ccSample(const CCVector3& v)
    : m_radius_(1)
    , ccStratigraphicPositionableElement(spc::SamplePtr(new spc::Sample(v.x, v.y, v.z)))
{
    m_selectionBehavior = SELECTION_IGNORED;
}

QIcon ccSample::getIcon() const
{
    if (getSample()->getManual())
        return QIcon(QString::fromUtf8(":/toolbar/icons/sample.png"));
    else
        return QIcon(QString::fromUtf8(":/toolbar/icons/sample_locked.png"));
}

ccBBox ccSample::getMyOwnBB()
{
    CCVector3 center = CCVector3::fromArray(getSample()->getPosition().data());
    float s = 0.1; //10 cm

    CCVector3 scale_v(s, s, s);
    CCVector3 min_corner(center - scale_v);
    CCVector3 max_corner(center + scale_v);
    ccBBox box(min_corner, max_corner);

    return box;
}

Sample::Ptr ccSample::getSample() const
{
    return getSPCElement<spc::Sample>();
}
