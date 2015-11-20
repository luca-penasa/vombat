#include "NewRoi.h"

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
#include <dialogs/ccPointPickingDlg.h>

//#include <ccGLWindow.h>

#include <ccDBRoot.h>


NewRoi::NewRoi(ccPluginInterface *parent_plugin): BaseFilter(FilterDescription("From a cloud representing a polygon create a selection",
                                                                     "From a cloud representing a polygon create a selection",
                                                                     "From a cloud representing a polygon create a selection",
                                                                     ":/toolbar/icons/selection.png"), parent_plugin)
{


}

int NewRoi::compute()
{
    return 1;
}

int NewRoi::openInputDialog()
{




//    std::vector<cc2DLabel*> picked;
//    vombat::theInstance()->getMainAppInterface()->doPickPoints(picked);

//    std::cout << "picked " << picked.size() << std::endl;





    return 1;
}

int NewRoi::checkParameters()
{
//    ccHObject::Container cont = vombat::theInstance()->getSelectedKindOf(CC_TYPES::POINT_CLOUD);

//    if (cont.size() == 0)
//        return -1;
//    else
    return 1;
}

int NewRoi::checkSelected()
{
    return 1;
}



