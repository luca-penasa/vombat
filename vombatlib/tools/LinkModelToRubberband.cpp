#include "LinkModelToRubberband.h"
#include <ccoutofcore/ccAttitude.h>
#include <ccoutofcore/ccSingleAttitudeModel.h>


#include <iostream> // for debug
#include <string>

#include <vombat.h>

#include <helpers/qtHelper.h>





LinkModelToRubberband::LinkModelToRubberband(ccPluginInterface *parent_plugin) : BaseFilter(FilterDescription(   "Link a stratigraphic model to a specific rubberband",
                                                                                                     "Link a stratigraphic model to a specific rubberband",
                                                                                                     "Link a stratigraphic model to a specific rubberband",
                                                                                                     ":/toolbar/icons/LinkModelToRubberband.png"), parent_plugin)
{
    this->setShowProgressBar(false);
}

int LinkModelToRubberband::compute()
{
    ccHObject::Container model  = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::StratigraphicModelBase::Type);
    ccHObject::Container rubberband  = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::SelectionRubberband::Type);


    ccMyBaseObject * mod = dynamic_cast<ccMyBaseObject *> (model.at(0));
    ccMyBaseObject * rub = dynamic_cast<ccMyBaseObject *> (rubberband.at(0));

    mod->getParent()->detachChild(mod);


    //! the model will become a child of model
    rub->addChild(mod);








    spc::StratigraphicModelBase::Ptr m = spcDynamicPointerCast<spc::StratigraphicModelBase>(mod->getSPCElement());

    spc::SelectionRubberband::Ptr s =  spcDynamicPointerCast<spc::SelectionRubberband>(rub->getSPCElement());

    CHECK(m != NULL) << "null ptr" ;
    CHECK(s != NULL) << "null ptr" ;
    s->linkToStratigraphicModel(m);


    vombat::theInstance()->getMainAppInterface()->refreshAll();


    return 1;
}








