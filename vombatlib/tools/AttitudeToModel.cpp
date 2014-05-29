#include "AttitudeToModel.h"
#include <ccoutofcore/ccAttitude.h>
#include <ccoutofcore/ccSingleAttitudeModel.h>


#include <iostream> // for debug
#include <string>

#include <vombat.h>

#include <helpers/qtHelper.h>





AttitudeToModel::AttitudeToModel(ccPluginInterface *parent_plugin) : BaseFilter(FilterDescription(   "Create Stratigraphic Model from one attitude",
                                                                                                     "Create Stratigraphic Model from one attitude",
                                                                                                     "Create Stratigraphic Model from one attitude",
                                                                                                     ":/toolbar/icons/AttitudeToModel.png"), parent_plugin)
{
    this->setShowProgressBar(false);
}


int AttitudeToModel::compute()
{



    ccHObject * selected = getSelectedEntityAsCCHObject(); //we are sure it exists!

    ccAttitude * att =dynamic_cast<ccAttitude *> (selected);

    if (!att)
        return -1;




    ccSingleAttitudeModel * model = new ccSingleAttitudeModel (*att);

    selected->addChild(model);

    QString def_name ("Single Attitude Model");
    def_name = suggestHObjectIncrementalName(model, def_name);
    model->setName(def_name);
    newEntity(model);



    return 1;
}




int AttitudeToModel::checkSelected()
{
    ccHObject * selected = getSelectedEntityAsCCHObject();
    if (selected && selected->getMetaData("class_name") == "ccAttitude")
        return 1;
    else
        return 0;
}
