#pragma once
#ifndef CC_EXAMPLE_OBJECT_H
#define CC_EXAMPLE_OBJECT_H

#include <ccoutofcore/ccSPCElementShell.h>
#include <QIcon>

namespace spc {
spcFwdDeclSharedPtr(ElementBase)
}

///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological attitude
///
class ccExampleObject : public ccSPCElementShell {
public:
    ccExampleObject(spc::ElementBasePtr obj);

    ~ccExampleObject()
    {
    }

    //inherited methods (ccHObject)
    virtual bool hasColors() const { return true; }
    virtual ccBBox getMyOwnBB()
    {
        //! example
        //        CCVector3 center = CCVector3::fromArray (getAttitude()->getPosition().data());
        //        float s = m_scale * 0.5;

        //        CCVector3 scale_v (s,s,s);
        //        CCVector3 min_corner(center - scale_v);
        //        CCVector3 max_corner(center + scale_v);
        //        ccBBox box(min_corner, max_corner);

        //        return box;
    }

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/attitude.png"));
    }

    //inherited from ccSerializableObject
    virtual bool isSerializable() const
    {
        return true;
    }

protected:
    virtual bool toFile_MeOnly(QFile& out) const
    {
        //        ccCustomHObject::toFile_MeOnly(out);

        //        QDataStream outs(&out);
        //        outs << m_scale;
        //        outs << m_width;

        //        ccSPCObjectsStreamer::WriteToQFile(m_attitude, out);
        //        return true;
    }
    virtual bool fromFile_MeOnly(QFile& in, short dataVersion, int flags)
    {
        //        ccCustomHObject::fromFile_MeOnly(in, dataVersion, flags);

        //        QDataStream ins(&in);
        //        ins >> m_scale;
        //        ins >> m_width;

        //        spc::ISerializable::Ptr ptr = ccSPCObjectsStreamer::ReadFromQFile(in);
        //        m_attitude = spcStaticPointerCast<spc::Attitude>(ptr);

        //        return true;
    }

    virtual void drawMeOnly(CC_DRAW_CONTEXT& context)
    {
        //! example of drawing
        //        if (MACRO_Draw3D(context))
        //        {
        //            bool pushName = MACRO_DrawEntityNames(context);

        //            if (pushName)
        //            {
        //                //not particulary fast
        //                if (MACRO_DrawFastNamesOnly(context))
        //                    return;
        //                glPushName(getUniqueID());
        //            }

        //            glPushAttrib(GL_LINE_BIT);
        //            glLineWidth(m_width);

        //            //we draw the segments
        //            if (isSelected())
        //                glColor3ubv(ccColor::red);
        //            else
        //                glColor3ubv(ccColor::green);

        //            Vector3f pos = getAttitude()->getPosition();

        //            Vector3f dip_v = getAttitude()->getDipVector();
        //            Vector3f strike_v = getAttitude()->getStrikeVector();

        //            Vector3f arr_shaft = pos + dip_v * m_scale * context.pickedPointsRadius;
        //            Vector3f strike_dir = pos + strike_v * m_scale * 0.5  * context.pickedPointsRadius;
        //            Vector3f s_opp = pos - strike_v * m_scale * 0.5 * context.pickedPointsRadius;

        //            context.display->display3DLabel(getAttitude()->getDipAndDipAngleAsString().c_str(), CCVector3(pos(0), pos(1), pos(2)), ccColor::red);

        //            glBegin(GL_LINES);
        //            glColor3ubv(ccColor::red);

        //            glVertex3fv( pos.data() );
        //            glVertex3fv( arr_shaft.data() );

        //            glColor3ubv(ccColor::blue);

        //            glVertex3fv( pos.data());
        //            glVertex3fv( strike_dir.data());

        //            glVertex3fv( pos.data());
        //            glVertex3fv( s_opp.data() );
        //            glEnd();

        //            glPopAttrib();

        //            if (pushName)
        //                glPopName();

        //        }
    }

}; //end class

#endif // CCPLANEORIENTATION_H
