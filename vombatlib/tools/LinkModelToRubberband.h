#ifndef LINK_MODEL_TO_RUBBERBAND_H
#define LINK_MODEL_TO_RUBBERBAND_H

//#include <BaseFilter.h>
#include "BaseFilter.h"
#include <dialogs/ccHObjectSelectionDlgSimple.h>

#include <spc/elements/StratigraphicModelSingleAttitude.h>

#include <ccoutofcore/ccSingleAttitudeModel.h>

#include <spc/elements/SelectionRubberband.h>




class LinkModelToRubberband : public BaseFilter
{
public:    
    LinkModelToRubberband(ccPluginInterface * parent_plugin = 0);

    ~LinkModelToRubberband()
    {

    }


    virtual int compute();

protected:
    virtual int checkSelected()
    {
        ccHObject::Container model  = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::StratigraphicModelBase::Type);
        ccHObject::Container rubberband  = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::SelectionRubberband::Type);

        if (model.size() == 1 && rubberband.size() == 1)
            return 1;
        else
            return 0;
    }
};

#endif // ATTITUDE_TO_MDOEL_H
