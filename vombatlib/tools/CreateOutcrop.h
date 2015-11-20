#ifndef CREATE_OUTCROP_H
#define CREATE_OUTCROP_H

#include "BaseFilter.h"
#include <spc/elements/VirtualOutcrop.h>
#include <ccVirtualOutcrop.h>
#include <ccSingleAttitudeModel.h>
class CreateOutcrop : public BaseFilter
{
public:
    CreateOutcrop(ccPluginInterface * parent_plugin = 0);


    // BaseFilter interface
public:
    int compute()
    {

        if (vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::VirtualOutcrop::Type).size() == 1
                && vombat::theInstance()->getSelected().size() == 1)
        {
            //! just update the existient model
            ccHObject * obj = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::VirtualOutcrop::Type).at(0);

            ccSPCElementShell * el = dynamic_cast<ccSPCElementShell *> (obj);

            spc::VirtualOutcrop::Ptr vo = el->getSPCElement<spc::VirtualOutcrop>();




            LOG(INFO) << "going to solve...";
            vo->solveStratigraphy();

            for (spc::ElementBase::Ptr a: vo->getChildsThatAre(&spc::StratigraphicModelBase::Type))
            {
                ccHObject* obj = vombat::theInstance()->getObjectFromElement(a);

                ccSingleAttitudeModel * o = dynamic_cast<ccSingleAttitudeModel *> (obj);
                if (o)
                    o->updateInternals();


            }


            return 1;
        }

        else // create a new one
        {
            spc::VirtualOutcrop::Ptr outcrop (new spc::VirtualOutcrop);
            ccVirtualOutcrop * out =  new ccVirtualOutcrop(outcrop);

            newEntity(out);

            return 1;
        }
    }
protected:
    int checkSelected()
    {
        if (vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::VirtualOutcrop::Type).size() == 1
                && vombat::theInstance()->getSelected().size() == 1)
        {
            return 1;
        }

        if (vombat::theInstance()->getSelected().size() != 0 )
        {
            return 0;
        }

        return 1;
    }

    int openInputDialog()
    {
        return 1;
    }
};

#endif // CreateOutcrop_H
