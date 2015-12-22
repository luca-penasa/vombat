#include "AttitudeToModel.h"
#include <ccoutofcore/ccAttitude.h>
#include <ccoutofcore/ccSingleAttitudeModel.h>

#include <iostream> // for debug
#include <string>

#include <vombat.h>

#include <helpers/qtHelper.h>

#include <dialogs/ccHObjectSelectionDlgSimple.h>

#include <spc/elements/StratigraphicModelSingleAttitude.h>

#include <ccoutofcore/ccSingleAttitudeModel.h>

AttitudeToModel::AttitudeToModel(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Create Stratigraphic Model from one attitude",
                     "Create Stratigraphic Model from one attitude",
                     "Create Stratigraphic Model from one attitude",
                     ":/toolbar/icons/AttitudeToModel.png"),
          parent_plugin)
{
    this->setShowProgressBar(false);
}

AttitudeToModel::~AttitudeToModel()
{
    //we must delete parent-less dialogs ourselves!
    if (m_dialog && m_dialog->parent() == 0)
        delete m_dialog;
}

int AttitudeToModel::compute()
{
    ccHObject* selected = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::Attitude::Type).at(0); //we are sure it exists!

    ccAttitude* att = dynamic_cast<ccAttitude*>(selected);

    if (!att)
        return -1;

    spc::StratigraphicModelSingleAttitude::Ptr modelspc(new spc::StratigraphicModelSingleAttitude(*att->getAttitude()));

    ccSingleAttitudeModel* model = new ccSingleAttitudeModel(modelspc);

    selected->addChild(model);

    QString def_name("Single Attitude Model");
    def_name = suggestHObjectIncrementalName(model, def_name);
    model->setName(def_name);
    newEntity(model);

    return 1;
}

int AttitudeToModel::checkSelected()
{

    if (vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::Attitude::Type).size() == 1) {
        return 1;
    }
    else
        return 0;
}
