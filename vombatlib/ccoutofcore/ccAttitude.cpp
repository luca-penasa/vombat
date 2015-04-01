#include "ccAttitude.h"
#include <iostream>

#include <helpers/ccSPCObjectsStreamer.h>
#include <ccGenericGLDisplay.h>

ccAttitude::ccAttitude(CCVector3 center, CCVector3 orientation):
    ccSPCElementShell(spc::Attitude::Ptr(new spc::Attitude(asEigenVector(orientation), asEigenVector(center))))
{
    m_attitude  = this->getSPCElement<spc::Attitude>();
     m_selectionBehavior = SELECTION_IGNORED;

     if (m_attitude->getNormal()(2) < 0)
         flipNormal();

}

ccAttitude::ccAttitude(spc::Attitude att): ccSPCElementShell(spc::Attitude::Ptr(new spc::Attitude(att)))
{        

    m_attitude = this->getSPCElement<spc::Attitude>();
    m_selectionBehavior = SELECTION_IGNORED;
    if (m_attitude->getNormal()(2) < 0)
        flipNormal();
}

ccAttitude::ccAttitude(spc::Attitude::Ptr att_ptr):m_attitude(att_ptr), ccSPCElementShell(att_ptr)
{

    setName(att_ptr->getDipAndDipAngleAsString().c_str());
    m_selectionBehavior = SELECTION_IGNORED;
    if (m_attitude->getNormal()(2) < 0)
        flipNormal();

}

void ccAttitude::flipNormal()
{
    m_attitude->setNormal(-m_attitude->getNormal());
}

ccBBox ccAttitude::getOwnBB()
{
    CCVector3 center = CCVector3::fromArray (getAttitude()->getPosition().data());
    float s = m_scale * 0.5;

    CCVector3 scale_v (s,s,s);
    CCVector3 min_corner(center - scale_v);
    CCVector3 max_corner(center + scale_v);
    ccBBox box(min_corner, max_corner);

	box.setValidity(true);
    return box;
}

bool ccAttitude::toFile_MeOnly(QFile &out) const
{
    ccCustomHObject::toFile_MeOnly(out);

    QDataStream outs(&out);
    outs << m_scale;
    outs << m_width;

    ccSPCObjectsStreamer::WriteToQFile(m_attitude, out);
    return true;

}

bool ccAttitude::fromFile_MeOnly(QFile &in, short dataVersion, int flags)
{
    ccCustomHObject::fromFile_MeOnly(in, dataVersion, flags);


    QDataStream ins(&in);
    ins >> m_scale;
    ins >> m_width;

    spc::ISerializable::Ptr ptr = ccSPCObjectsStreamer::ReadFromQFile(in);
    m_attitude = spcStaticPointerCast<spc::Attitude>(ptr);

    return true;
}


void ccAttitude::drawMeOnly(CC_DRAW_CONTEXT &context)
{

    if (MACRO_Draw3D(context))
    {
        bool pushName = MACRO_DrawEntityNames(context);

        if (pushName)
        {
            //not particulary fast
            if (MACRO_DrawFastNamesOnly(context))
                return;
            glPushName(getUniqueID());
        }


        glPushAttrib(GL_LINE_BIT);
        glLineWidth(m_width);


        //we draw the segments
        if (isSelected())
			glColor3ubv(ccColor::red.rgba);
        else
			glColor3ubv(ccColor::green.rgba);

        Vector3f pos = getAttitude()->getPosition();

        Vector3f dip_v = getAttitude()->getDipVector();
        Vector3f strike_v = getAttitude()->getStrikeVector();


		Vector3f arr_shaft = pos + dip_v * m_scale * context.labelMarkerSize;
		Vector3f strike_dir = pos + strike_v * m_scale * 0.5  * context.labelMarkerSize;
		Vector3f s_opp = pos - strike_v * m_scale * 0.5 * context.labelMarkerSize;


		QFont font(context._win->getTextDisplayFont()); // takes rendering zoom into
		// account!
		font.setPointSize(font.pointSize());
		font.setBold(true);
//
		glDisable(GL_DEPTH_TEST);
		context._win->display3DLabel(getAttitude()->getDipAndDipAngleAsString().c_str(), getAttitude()->getPosition().data(), ccColor::red.rgba, font);
		glEnable(GL_DEPTH_TEST);


        glBegin(GL_LINES);
		glColor3ubv(ccColor::red.rgba);

        glVertex3fv( pos.data() );
        glVertex3fv( arr_shaft.data() );


		glColor3ubv(ccColor::blue.rgba);


        glVertex3fv( pos.data());
        glVertex3fv( strike_dir.data());

        glVertex3fv( pos.data());
        glVertex3fv( s_opp.data() );
        glEnd();

        glPopAttrib();

        if (pushName)
            glPopName();

    }
}



