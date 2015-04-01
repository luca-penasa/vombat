#include "ccSample.h"
#include <ccGenericGLDisplay.h>
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

void ccSample::drawStratPos(CC_DRAW_CONTEXT &context)
{
    QFont font(context._win->getTextDisplayFont()); // takes rendering zoom into
    // account!
    font.setPointSize(font.pointSize());
    font.setBold(true);

//    // draw their name
//	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);


QString name = QString::fromStdString(getSample()->getElementName()) +
        " at SP: "+
        QString::number(getSample()->getStratigraphicPosition(), 'g', 3);

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
}

void ccSample::drawMeOnly(CC_DRAW_CONTEXT &context)
{

    if (MACRO_Draw3D(context))
    {
        if (!this->getSample())
            return;

        bool pushName = MACRO_DrawEntityNames(context);
        if (pushName) {
            // not particularily fast
            if (MACRO_DrawFastNamesOnly(context))
                return;
            glPushName(getUniqueIDForDisplay());
        }



        if (!c_unitPointMarker || c_unitPointMarker->getRadius() != m_radius_) {
            c_unitPointMarker = QSharedPointer
                    <ccSphere>(new ccSphere(m_radius_, 0, "PointMarker", 12));
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

        if (isSelected() && !pushName)
            c_unitPointMarker->setTempColor(ccColor::red);
        else
            c_unitPointMarker->setTempColor(ccColor::magenta);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();



        float x, y, z;
        this->getSample()->getPosition(x, y, z);
        //    const CCVector3* P = m_points[i].cloud->getPoint(m_points[i].index);
        ccGL::Translate(x, y, z);
		glScalef(context.labelMarkerSize, context.labelMarkerSize,
				 context.labelMarkerSize);

		m_current_scaling_ = context.labelMarkerSize;

        c_unitPointMarker->draw(markerContext);

        glPopMatrix();

        drawStratPos(context);

        if (pushName)
            glPopName();

    }
}
