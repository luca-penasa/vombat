#include "ccPlanarSelection.h"
#include <QIcon>
#include <spc/elements/SelectionRubberband.h>
#include <ccPolyline.h>
#include <spc/elements/Plane.h>


ccPlanarSelection::ccPlanarSelection(): ccSPCElementShell(spc::SelectionRubberband::Ptr(new spc::SelectionRubberband))
{



}

ccPlanarSelection::ccPlanarSelection(spc::SelectionRubberbandPtr sel): ccSPCElementShell(sel)
{
    LOG(INFO) << "ccPlanarSelection created";


}

ccBBox ccPlanarSelection::getOwnBB(bool withGLFeatures)
{
    CHECK(getRubberband() != nullptr);

    m_selectionBehavior = SELECTION_IGNORED;
    spc::BoundingBox<float, 3> bb= getRubberband()->getVertices().getBB();

    CCVector3 min (bb.min_.data());
    CCVector3 max (bb.max_.data());

    return ccBBox(min, max);
}

QIcon ccPlanarSelection::getIcon() const
{
    return QIcon(QString::fromUtf8(":/toolbar/icons/selection.png"));
}

void ccPlanarSelection::drawMeOnly(CC_DRAW_CONTEXT &context)
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

        size_t vertCount = this->getRubberband()->getVertices().getNumberOfPoints();
        if (vertCount < 2)
            return;

        if (m_width != 0)
        {
            glPushAttrib(GL_LINE_BIT);
            glLineWidth(static_cast<GLfloat>(m_width));


            //            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            //we draw the segments
            if (isSelected())
                glColor3ubv(ccColor::red.rgba);
            else
                glColor3ubv(ccColor::green.rgba);


            for (int i = -1; i <= 1; ++i)
            {
                if (i == 0)
                    continue;
                Eigen::Vector3f n =  getRubberband()->getProjectionPlane()->getUnitNormal() * (float) i * getRubberband()->getMaxDistance();
                glBegin(GL_LINE_LOOP);
                for( int i = 0 ; i < getRubberband()->getVertices().getNumberOfPoints(); ++i)
                {
                    Eigen::Vector3f p = getRubberband()->getVertices().getPoint(i) + n;
                    ccGL::Vertex3v( p.data() );
                }
                glEnd();
            }
        }

        glBegin(GL_LINES);
        for( int i = 0 ; i < getRubberband()->getVertices().getNumberOfPoints(); ++i)
        {
            Eigen::Vector3f in =  getRubberband()->getProjectionPlane()->getUnitNormal() * getRubberband()->getMaxDistance();
            //                Eigen::Vector3f out = -in;

            Eigen::Vector3f p1 = getRubberband()->getVertices().getPoint(i) + in;
            Eigen::Vector3f p2 = getRubberband()->getVertices().getPoint(i) - in;
            //            LOG(INFO) << getRubberband()->getVertices().getPoint(i).transpose();
            ccGL::Vertex3v(p1.data());
            ccGL::Vertex3v(p2.data());
        }
        glEnd();




        if (m_width != 0)
        {
            glPopAttrib();
        }

        if (pushName)
            glPopName();
    }
}

SelectionRubberband::Ptr ccPlanarSelection::getRubberband() const
{
    return this->getSPCElement<spc::SelectionRubberband>();
}
