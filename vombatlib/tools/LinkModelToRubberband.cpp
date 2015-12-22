#include "LinkModelToRubberband.h"
#include <ccoutofcore/ccAttitude.h>
#include <ccoutofcore/ccSingleAttitudeModel.h>

#include <iostream> // for debug
#include <string>

#include <vombat.h>

#include <helpers/qtHelper.h>

#include <dialogs/ccHObjectSelectionDlgSimple.h>

#include <spc/elements/StratigraphicModelSingleAttitude.h>

#include <ccoutofcore/ccSingleAttitudeModel.h>

#include <spc/elements/SelectionRubberband.h>

LinkModelToRubberband::LinkModelToRubberband(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Link a stratigraphic model to a specific rubberband",
                     "Link a stratigraphic model to a specific rubberband",
                     "Link a stratigraphic model to a specific rubberband",
                     ":/toolbar/icons/LinkModelToRubberband.png"),
          parent_plugin)
{
    this->setShowProgressBar(false);
}

int LinkModelToRubberband::compute()
{
    ccHObject::Container model = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::StratigraphicModelBase::Type);
    ccHObject::Container rubberband = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::SelectionRubberband::Type);

    ccSPCElementShell* mod = dynamic_cast<ccSPCElementShell*>(model.at(0));
    ccSPCElementShell* rub = dynamic_cast<ccSPCElementShell*>(rubberband.at(0));

    mod->getParent()->detachChild(mod);

    //! the model will become a child of model
    rub->addChild(mod);

    spc::StratigraphicModelBase::Ptr m = spcDynamicPointerCast<spc::StratigraphicModelBase>(mod->getSPCElement());

    spc::SelectionRubberband::Ptr s = spcDynamicPointerCast<spc::SelectionRubberband>(rub->getSPCElement());

    CHECK(m != NULL) << "null ptr";
    CHECK(s != NULL) << "null ptr";
    s->linkToStratigraphicModel(m);

    vombat::theInstance()->getMainAppInterface()->refreshAll();

    return 1;
}

int LinkModelToRubberband::checkSelected()
{
    ccHObject::Container model = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::StratigraphicModelBase::Type);
    ccHObject::Container rubberband = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::SelectionRubberband::Type);

    if (model.size() == 1 && rubberband.size() == 1)
        return 1;
    else
        return 0;
}
