#ifndef FlipModel_H
#define FlipModel_H

#include "BaseFilter.h"
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <spc/elements/StratigraphicModelSingleAttitude.h>
#include <ScalarField.h>
class FlipModel : public BaseFilter
{
public:
    FlipModel(ccPluginInterface * parent_plugin = 0);

    // BaseFilter interface
public:
    int compute();

protected:
    int checkSelected()
    {

        if (vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::StratigraphicModelSingleAttitude::Type).size() >= 1)
            return 1;
        else
            return 0;
    }

    int openInputDialog()
    {
        return 1;
    }
};

#endif // FlipModel_H
