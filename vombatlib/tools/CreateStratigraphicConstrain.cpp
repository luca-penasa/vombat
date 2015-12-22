#include "CreateStratigraphicConstrain.h"
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <ScalarField.h>

#include <spc/elements/MovableElement.h>

#include <ccStratigraphicConstrain.h>
#include <spc/elements/StratigraphicConstrain.h>
#include <vombat.h>

CreateStratigraphicConstrain::CreateStratigraphicConstrain(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Create a stratigraphic constrain between samples or points",
                     "Create a stratigraphic constrain between samples or points",
                     "Create a stratigraphic constrain between samples or points",
                     ":/toolbar/icons/stratigraphic_constrain.png"),
          parent_plugin)
{
    this->setShowProgressBar(false);
}

int CreateStratigraphicConstrain::compute()
{

    DLOG(INFO) << "going to compue!";

    ccHObject::Container objects = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::Point3D::Type);

    spc::StratigraphicConstrain::Ptr constrain(new spc::StratigraphicConstrain);

    DLOG(INFO) << "going to cycle on objects";

    ccStratigraphicConstrain* out = new ccStratigraphicConstrain(constrain);

    for (ccHObject* obj : objects) {

        DLOG(INFO) << "working on " << obj;

        ccSPCElementShell* myobj = dynamic_cast<ccSPCElementShell*>(obj);

        CHECK(myobj != NULL) << "Bad error. pointer is null!";

        spc::StratigraphicPositionableElement::Ptr point_ptr = spcDynamicPointerCast<spc::StratigraphicPositionableElement>(myobj->getSPCElement());

        CHECK(point_ptr != NULL) << "Bad error. pointer is null!";

        constrain->addVertex(point_ptr);

        obj->setLocked(true);

        //            ccSample * sam = new ccSample(point_ptr);
        //            out->addChild(sam);
        //            sam->setVisible(true);
    }

    out->setVisible(true);
    emit newEntity(out);

    return 1;
}

int CreateStratigraphicConstrain::checkSelected()
{
    ccHObject::Container selected = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::StratigraphicPositionableElement::Type);

    if (selected.size() >= 2)
        return 1;
    else
        return -1;
}
