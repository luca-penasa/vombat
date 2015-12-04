#ifndef CCPLANARSELECTION_H
#define CCPLANARSELECTION_H


#include <spc/elements/SelectionRubberband.h>
#include <ccoutofcore/ccSPCElementShell.h>
#include <ccPolyline.h>
//#include <pcl/common/common.h>
//#include <pcl/filters/extract_indices.h>
#include <boost/foreach.hpp>

class ccPlanarSelection: public ccSPCElementShell
{
public:
    ccPlanarSelection();

    ccPlanarSelection(spc::SelectionRubberband::Ptr sel): ccSPCElementShell(sel)
    {       
        LOG(INFO) << "ccPlanarSelection created";

//        m_foreground = false;

//        m_selectionBehavior = SELECTION_IGNORED;
//        m_width  = 0.0;
//    //	memcpy(m_rgbColor, ccColor::green.rgba, sizeof(colorType) * 3);

//        m_rgbColor = ccColor::green;
//        setVisible(true);
    }

    virtual bool isSerializable() const override
    { return true; }

    virtual bool hasColors() const override
    { return true; }


//    virtual ccBBox getMyOwnBB() override;

	virtual ccBBox getOwnBB(bool withGLFeatures = false) override;


    virtual QIcon getIcon() const override
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/selection.png"));
    }

protected:
    virtual void drawMeOnly(CC_DRAW_CONTEXT &context) override
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
                Eigen::Vector3f n =  getRubberband()->getProjectionPlane().getUnitNormal() * (float) i * getRubberband()->getMaxDistance();
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
                Eigen::Vector3f in =  getRubberband()->getProjectionPlane().getUnitNormal() * getRubberband()->getMaxDistance();
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
public:
    void setColor(const ccColor::Rgb & col)
    {
        m_rgbColor = col;
    }

    void setWidth(PointCoordinateType width)
    {
        m_width = width;
    }

    const ccColor::Rgb getColor() const
    {
        return m_rgbColor;
    }

    spc::SelectionRubberband::Ptr getRubberband() const
    {
        return this->getSPCElement<spc::SelectionRubberband>();
    }




protected:
    //    virtual void applyGLTransformation(const ccGLMatrix& trans) {}
    //    virtual void setGLTransformation(const ccGLMatrix& trans) {}

    //! Unique RGB color
//    colorType m_rgbColor[3];

    ccColor::Rgb m_rgbColor;

    //! Width of the line
    PointCoordinateType m_width = 2;
//    spc::SelectionRubberband::Ptr getRubberband();


    //! Whether poyline should draws itself in background (false) or foreground (true)
    bool m_foreground;





};

#endif // CCPLANARSELECTION_H
