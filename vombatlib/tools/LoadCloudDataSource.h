#pragma once
#ifndef LOAD_CLOUD_DATA_SOURCE_H
#define LOAD_CLOUD_DATA_SOURCE_H

#include "BaseFilter.h"

class LoadCloudDataSource : public BaseFilter
{
public:
    LoadCloudDataSource(ccPluginInterface * parent_plugin = 0);

    // BaseFilter interface
public:
    int compute();

protected:
    int checkSelected();

    int openInputDialog()
    {
        return 1;
    }
};

#endif // ADDSAMPLE_H
