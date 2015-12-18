#include "CloudToPlanarSelection.h"

//#include <ccGraphicalSegmentationTool.h>

#include <ccPointCloud.h>

#include <vombat.h>

//#include <ccGLWindow.h>

//#include <cc2DRubberbandLabel.h>

#include <ccPolyline.h>

#include <ccoutofcore/ccPlanarSelection.h>
#include <iostream>
#include <cc2DViewportLabel.h>

#include <qPCL/PclUtils/utils/cc2sm.h>
#include <helpers/spcCCPointCloud.h>

#include <ccHObjectCaster.h>


CloudToPlanarSelection::CloudToPlanarSelection(ccPluginInterface *parent_plugin): BaseFilter(FilterDescription("From a cloud representing a polygon create a selection",
                                                                     "From a cloud representing a polygon create a selection",
                                                                     "From a cloud representing a polygon create a selection",
                                                                     ":/toolbar/icons/selection.png"), parent_plugin)
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

    if (cont.size() == 0)
        return -1;

    ccPointCloud * verts = ccHObjectCaster::ToPointCloud(cont.at(0) );

    if (!verts)
        return -1;


    LOG(INFO) << "get as spc point cloud";
    spcCCPointCloud::Ptr c =  spcCCPointCloud::fromccPointCloud(verts);

    if (c->getNumberOfPoints() >= 40)
    {
        LOG(ERROR) << "too much points here. Cannot create a selction with all these points";
        return -1;
    }



    LOG(INFO) << "now create rubberband";
    spc::SelectionRubberband::Ptr sel (new spc::SelectionRubberband(*c));
    ccPlanarSelection * pl = new ccPlanarSelection(sel);
    pl->setVisible(true);
    LOG(INFO) << "now call newEntity";
    newEntity(pl);



    return 1;
}

int CloudToPlanarSelection::checkParameters()
{
    ccHObject::Container cont = vombat::theInstance()->getSelectedKindOf(CC_TYPES::POINT_CLOUD);

    if (cont.size() == 0)
        return -1;
    else
        return 1;
}



