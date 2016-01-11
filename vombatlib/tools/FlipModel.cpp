#include "FlipModel.h"
#include <ccSingleAttitudeModel.h>

#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <spc/elements/StratigraphicModelSingleAttitude.h>
#include <ScalarField.h>
#include <vombat.h>



FlipModel::FlipModel(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Flip the direction of the stratigraphic model",
                     "Flip the direction of the stratigraphic model",
                     "Flip the direction of the stratigraphic model",
                     ":/toolbar/icons/FlipModel.png"),
          parent_plugin)
{
    this->setShowProgressBar(false);
}

int FlipModel::compute()
{

    std::vector<ccHObject*> to_flip = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::StratigraphicModelSingleAttitude::Type);

    for (ccHObject* o : to_flip) {
        ccSPCElementShell* shell = dynamic_cast<ccSPCElementShell*>(o);

        spc::StratigraphicModelSingleAttitude::Ptr model = shell->getSPCElement<spc::StratigraphicModelSingleAttitude>();

        model->setNormal(-model->getNormal());

        ccSingleAttitudeModel* ccmodel = dynamic_cast<ccSingleAttitudeModel*>(o);

        ccmodel->updateInternals();
        entityHasChanged(ccmodel);
    }

    return 1;
}

int FlipModel::checkSelected()
{

    if (vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::StratigraphicModelSingleAttitude::Type).size() >= 1)
        return 1;
    else
        return 0;
}
