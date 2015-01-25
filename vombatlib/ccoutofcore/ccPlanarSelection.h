#ifndef CCPLANARSELECTION_H
#define CCPLANARSELECTION_H


#include <spc/elements/SelectionRubberband.h>
#include <ccoutofcore/ccSPCElementShell.h>
#include <ccPolyline.h>
#include <pcl/common/common.h>
#include <pcl/filters/extract_indices.h>
#include <boost/foreach.hpp>

class ccPlanarSelection: public ccSPCElementShell
{
public:
    ccPlanarSelection();

    ccPlanarSelection(spc::SelectionRubberband::Ptr sel): rubberband_(sel), ccSPCElementShell(sel)
    {       
        LOG(INFO) << "ccPlanarSelection created";
    }

    virtual bool isSerializable() const override
    { return true; }

    virtual bool hasColors() const override
    { return true; }


//    virtual ccBBox getMyOwnBB() override;

    virtual ccBBox getDisplayBB() override;


    virtual QIcon getIcon() const override
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/selection.png"));
    }

protected:
    virtual void drawMeOnly(CC_DRAW_CONTEXT &context) override
    {

        //we draw here a little 3d representation of the sensor and some of its attributes
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

            size_t vertCount = this->rubberband_->getVertices().getNumberOfPoints();
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
                Eigen::Vector3f n =  rubberband_->getProjectionPlane().getUnitNormal() * (float) i * rubberband_->getMaxDistance();
                glBegin(GL_LINE_LOOP);
                for( int i = 0 ; i < rubberband_->getVertices().getNumberOfPoints(); ++i)
                {
                    Eigen::Vector3f p = rubberband_->getVertices().getPoint(i) + n;
                    ccGL::Vertex3v( p.data() );
                }
                glEnd();
            }
            }

            glBegin(GL_LINES);
            for( int i = 0 ; i < rubberband_->getVertices().getNumberOfPoints(); ++i)
            {
                Eigen::Vector3f in =  rubberband_->getProjectionPlane().getUnitNormal() * rubberband_->getMaxDistance();
//                Eigen::Vector3f out = -in;

                Eigen::Vector3f p1 = rubberband_->getVertices().getPoint(i) + in;
                Eigen::Vector3f p2 = rubberband_->getVertices().getPoint(i) - in;
                //            LOG(INFO) << rubberband_->getVertices().getPoint(i).transpose();
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
    PointCoordinateType m_width = 2;
    spc::SelectionRubberband::Ptr rubberband_;


    //! Whether poyline should draws itself in background (false) or foreground (true)
    bool m_foreground;





};

#endif // CCPLANARSELECTION_H
