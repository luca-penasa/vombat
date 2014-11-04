#ifndef CCPLANARSELECTION_H
#define CCPLANARSELECTION_H


#include <spc/elements/SelectionRubberband.h>
#include <ccoutofcore/ccMyBaseObject.h>
#include <ccPolyline.h>
#include <pcl/common/common.h>
#include <pcl/filters/extract_indices.h>
#include <boost/foreach.hpp>

class ccPlanarSelection: public ccMyBaseObject
{
public:
    ccPlanarSelection();

    ccPlanarSelection(spc::SelectionRubberband::Ptr sel)
    {
        rubberband_ = sel;
    }

    virtual bool isSerializable() const { return true; }
    virtual bool hasColors() const { return true; }
    virtual ccBBox getMyOwnBB()
    {                
        DCHECK(rubberband_ != NULL);
        Vector4f mincorner;
        Vector4f maxcorner;
//!\todo to fix
//        pcl::getMinMax3D(*rubberband_->getVertices(), mincorner, maxcorner);

        CCVector3 min = CCVector3(mincorner.data());
        CCVector3 max = CCVector3(maxcorner.data());
        return ccBBox(min, max);
    }


    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/selection.png"));
    }

    virtual void drawMeOnly(CC_DRAW_CONTEXT &context)
    {
        size_t vertCount = this->rubberband_->getVertices().getNumberOfPoints();
        if (vertCount < 2)
            return;

        if (colorsShown())
            glColor3ubv(m_rgbColor);

        if (m_width != 0)
        {
            glPushAttrib(GL_LINE_BIT);
            glLineWidth(static_cast<GLfloat>(m_width));
        }

        glBegin(GL_LINE_LOOP);

        ///! \todo fix this
//        for( const pcl::PointXYZ &p: *this->rubberband_->getVertices())
//        {
//            ccGL::Vertex3v(p.data);
//        }

        glEnd();

        if (m_width != 0)
        {
            glPopAttrib();
        }
    }

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

    virtual QString getSPCClassName() const
    {
        return "ccPlanarSelection";
    }


protected:
    virtual void applyGLTransformation(const ccGLMatrix& trans) {}
    virtual void setGLTransformation(const ccGLMatrix& trans) {}

    //! Unique RGB color
    colorType m_rgbColor[3];

    //! Width of the line
    PointCoordinateType m_width;
public:
    spc::SelectionRubberband::Ptr rubberband_;
protected:

    //! Whether poyline should draws itself in background (false) or foreground (true)
    bool m_foreground;


    virtual spc::ElementBase::Ptr getSPCElement() const
    {
        DCHECK(rubberband_!=NULL);
        return rubberband_;
    }




};

#endif // CCPLANARSELECTION_H
