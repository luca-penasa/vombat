#include "ccPlanarSelection.h"

ccPlanarSelection::ccPlanarSelection()
{

    QVariant var("An area selection");
    setMetaData(QString("[vombat][ccPlanarSelection]"), var);

    m_foreground = false;

    m_selectionBehavior = SELECTION_IGNORED;
    m_width  = 0.0;
    memcpy(m_rgbColor, ccColor::green, sizeof(colorType) * 3);

    setVisible(true);



}

ccBBox ccPlanarSelection::getDisplayBB()
{
    CHECK(rubberband_ != NULL);

    m_selectionBehavior = SELECTION_IGNORED;
    spc::BoundingBox<float, 3> bb= rubberband_->getVertices().getBB();

    CCVector3 min (bb.min_.data());
    CCVector3 max (bb.max_.data());

    return ccBBox(min, max);
}
