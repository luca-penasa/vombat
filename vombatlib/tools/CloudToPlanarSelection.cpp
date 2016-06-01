#include "CloudToPlanarSelection.h"
#include <ccPointCloud.h>

#include <vombat.h>
#include <ccPolyline.h>
#include <spc/elements/SelectionRubberband.h>
#include <ccoutofcore/ccPlanarSelection.h>
#include <iostream>
#include <cc2DViewportLabel.h>

#include <qPCL/PclUtils/utils/cc2sm.h>
#include <helpers/spcCCPointCloud.h>

#include <ccHObjectCaster.h>

CloudToPlanarSelection::CloudToPlanarSelection(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("From a cloud representing a polygon create a selection",
                     "From a cloud representing a polygon create a selection",
                     "From a cloud representing a polygon create a selection",
                     ":/toolbar/icons/selection.png"),
          parent_plugin)
{
}

int CloudToPlanarSelection::compute()
{
    return 1;
}

int CloudToPlanarSelection::openInputDialog()
{
    this->setShowProgressBar(false);

    ccHObject::Container cont = vombat::theInstance()->getSelectedKindOf(CC_TYPES::POINT_CLOUD);

    ccHObject::Container plines = vombat::theInstance()->getSelectedKindOf(CC_TYPES::POLY_LINE);

    for (ccHObject* pline : plines) {
        ccPolyline* pl = dynamic_cast<ccPolyline*>(pline);

        ccPointCloud* asc = dynamic_cast<ccPointCloud*>(pl->getAssociatedCloud());
        if (asc)
            cont.push_back(asc);
    }

    if (cont.size() == 0)
        return -1;

    for (ccHObject* obj : cont)

    {

        ccPointCloud* verts = ccHObjectCaster::ToPointCloud(obj);

        if (!verts)
            return -1;

        DLOG(INFO) << "get as spc point cloud";
        spcCCPointCloud::Ptr c = spcCCPointCloud::fromccPointCloud(verts);

        if (c->getNumberOfPoints() >= 200) {
            DLOG(ERROR) << "too much points here. Cannot create a selction with all these points";
            return -1;
        }

        DLOG(INFO) << "now create rubberband";
        spc::SelectionRubberband::Ptr sel(new spc::SelectionRubberband(*c));
        ccPlanarSelection* pl = new ccPlanarSelection(sel);
        pl->setVisible(true);
        DLOG(INFO) << "now call newEntity";
        newEntity(pl);
    }

    return 1;
}

int CloudToPlanarSelection::checkSelected()
{
    ccHObject::Container cont = vombat::theInstance()->getSelectedKindOf(CC_TYPES::POINT_CLOUD);
    ccHObject::Container cont_pline = vombat::theInstance()->getSelectedThatAre(CC_TYPES::POLY_LINE);

    if (cont.size() == 0 & cont_pline.size() == 0)
        return -1;
    else
        return 1;
}
