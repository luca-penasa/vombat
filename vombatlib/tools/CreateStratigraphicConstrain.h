#ifndef CREATE_STRATIGRAPHIC_CONSTRAIN_H
#define CREATE_STRATIGRAPHIC_CONSTRAIN_H

#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <ScalarField.h>

#include <spc/elements/MovableElement.h>

#include <ccStratigraphicConstrain.h>
class CreateStratigraphicConstrain : public BaseFilter
{
public:
    CreateStratigraphicConstrain(ccPluginInterface * parent_plugin = 0);

    // BaseFilter interface
public:
    int compute()
    {

        DLOG(INFO) << "going to compue!";

        ccHObject::Container objects = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::Point3D::Type);


        spc::StratigraphicConstrain::Ptr constrain (new spc::StratigraphicConstrain);


        DLOG(INFO) << "going to cycle on objects";

        ccStratigraphicConstrain * out  = new ccStratigraphicConstrain(constrain);


        for(ccHObject * obj: objects)
        {

            DLOG(INFO) << "working on " << obj;

            ccSPCElementShell * myobj = dynamic_cast<ccSPCElementShell *> (obj);

            CHECK(myobj != NULL) << "Bad error. pointer is null!";

            spc::StratigraphicPositionableElement::Ptr point_ptr = spcDynamicPointerCast<spc::StratigraphicPositionableElement> (myobj->getSPCElement());

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

protected:
    int checkSelected()
    {
        ccHObject::Container selected = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::StratigraphicPositionableElement::Type);

        if (selected.size() >= 2)
            return 1;
        else
            return -1;
    }

    int openInputDialog()
    {
        return 1;
    }
};

#endif // ADDSAMPLE_H
