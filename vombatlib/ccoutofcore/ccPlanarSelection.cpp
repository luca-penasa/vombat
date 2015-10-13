#include "ccPlanarSelection.h"

ccPlanarSelection::ccPlanarSelection(): rubberband_(new spc::SelectionRubberband), ccSPCElementShell(rubberband_)
{
    m_foreground = false;

    m_selectionBehavior = SELECTION_IGNORED;
    m_width  = 0.0;
//	memcpy(m_rgbColor, ccColor::green.rgba, sizeof(colorType) * 3);

    m_rgbColor = ccColor::green;
    setVisible(true);
}

ccBBox ccPlanarSelection::getOwnBB(bool withGLFeatures)
{
    CHECK(rubberband_ != NULL);

    m_selectionBehavior = SELECTION_IGNORED;
    spc::BoundingBox<float, 3> bb= rubberband_->getVertices().getBB();

    CCVector3 min (bb.min_.data());
    CCVector3 max (bb.max_.data());

    return ccBBox(min, max);
}
