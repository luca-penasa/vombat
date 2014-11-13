#include "ccAttitude.h"
#include <iostream>

#include <helpers/ccSPCObjectsStreamer.h>
#include <ccGenericGLDisplay.h>

ccAttitude::ccAttitude(CCVector3 center, CCVector3 orientation)
{

    spc::Attitude att = spc::Attitude(asEigenVector(orientation), asEigenVector(center));
    setAttitude(att);
    writeSPCClassNameToMetadata();

            m_selectionBehavior = SELECTION_IGNORED;

}



ccAttitude::ccAttitude(spc::Attitude att)
{    
    setAttitude(att);
    writeSPCClassNameToMetadata();
                m_selectionBehavior = SELECTION_IGNORED;

}

ccAttitude::ccAttitude(spc::Attitude::Ptr att_ptr)
{
    setAttitude(att_ptr);
    setName(att_ptr->getDipAndDipAngleAsString().c_str());
    writeSPCClassNameToMetadata();
                m_selectionBehavior = SELECTION_IGNORED;

}


ccAttitude::ccAttitude()
{
    setAttitude(spc::Attitude::Ptr(new spc::Attitude));
    writeSPCClassNameToMetadata();
                m_selectionBehavior = SELECTION_IGNORED;

}

ccAttitude::ccAttitude(QString name): ccMyBaseObject(name)
{
    setAttitude(spc::Attitude::Ptr(new spc::Attitude));
    writeSPCClassNameToMetadata();
            m_selectionBehavior = SELECTION_IGNORED;

}

ccBBox ccAttitude::getMyOwnBB()
{
    CCVector3 center = CCVector3::fromArray (getAttitude()->getPosition().data());
    float s = m_scale * 0.5;

    CCVector3 scale_v (s,s,s);
    CCVector3 min_corner(center - scale_v);
    CCVector3 max_corner(center + scale_v);
    ccBBox box(min_corner, max_corner);

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
            glColor3ubv(ccColor::red);
        else
            glColor3ubv(ccColor::green);

        Vector3f pos = getAttitude()->getPosition();

        Vector3f dip_v = getAttitude()->getDipVector();
        Vector3f strike_v = getAttitude()->getStrikeVector();


        Vector3f arr_shaft = pos + dip_v * m_scale * context.pickedPointsRadius;
        Vector3f strike_dir = pos + strike_v * m_scale * 0.5  * context.pickedPointsRadius;
        Vector3f s_opp = pos - strike_v * m_scale * 0.5 * context.pickedPointsRadius;

        context._win->display3DLabel(getAttitude()->getDipAndDipAngleAsString().c_str(), CCVector3(pos(0), pos(1), pos(2)), ccColor::red);


        glBegin(GL_LINES);
        glColor3ubv(ccColor::red);

        glVertex3fv( pos.data() );
        glVertex3fv( arr_shaft.data() );


        glColor3ubv(ccColor::blue);


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



