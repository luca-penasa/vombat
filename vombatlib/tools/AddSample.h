#ifndef ADDSAMPLE_H
#define ADDSAMPLE_H

#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <ScalarField.h>
class AddSample : public BaseFilter
{
public:
    AddSample(ccPluginInterface * parent_plugin = 0);

    // BaseFilter interface
public:
    int compute();

protected:
    int checkSelected()
    {
        ccHObject::Container selected;
        getSelectedEntitiesThatAre(CC_TYPES::POINT_CLOUD, selected);
        getSelectedEntitiesThatAre(CC_TYPES::LABEL_2D, selected);

        if (selected.size() > 0)
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
