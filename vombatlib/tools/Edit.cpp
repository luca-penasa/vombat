#include "Edit.h"
#include <ccoutofcore/ccAttitude.h>
#include <ccoutofcore/ccSingleAttitudeModel.h>

#include <spc/elements/StratigraphicModelSingleAttitude.h>

#include <iostream> // for debug

#include <vombat.h>

#include <dialogs/ccHObjectSelectionDlgSimple.h>

#include <ccoutofcore/ccSingleAttitudeModel.h>

//Edit::Edit(ccPluginInterface* parent_plugin)
//    : BaseFilter(FilterDescription("Edit selected element",
//                     "Edit selected element",
//                     "Edit selected element",
//                     ":/toolbar/icons/edit.png"),
//          parent_plugin)
//{
//    this->setShowProgressBar(false);
//}

//int Edit::compute()
//{
//    ccHObject* selected = getSelectedEntityAsCCHObject(); //we are sure it exists!

//    ccSPCElementShell* myobj = static_cast<ccSPCElementShell*>(selected);
//    if (!myobj)
//        return 0;

//    myobj->showEditDlg();
//    return 1;
//}

//int Edit::checkSelected()
//{
//    ccHObject* selected = getSelectedEntityAsCCHObject();
//    if (selected && selected->getMetaData("class_name").isValid()) {

//        ccSPCElementShell* mobj = static_cast<ccSPCElementShell*>(selected);

//        if (!mobj) {
//            DLOG(WARNING) << "problem casting!";
//            return 0;
//        }

//        if (mobj->getHasEditDlg()) {
//            std::cout << "has edit dialog" << std::endl;
//            return 1;
//        }
//        else {
//            std::cout << "it does not have a edit dialog" << std::endl;
//        }
//    }
//    else
//        return 0;
//}
