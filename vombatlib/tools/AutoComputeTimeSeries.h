#pragma once
#ifndef AUTOCOMPUTE_TIME_SERIES_H
#define AUTOCOMPUTE_TIME_SERIES_H

#include "BaseFilter.h"

class AutoComputeTimeSeries : public BaseFilter {
public:
    AutoComputeTimeSeries(ccPluginInterface* parent_plugin = 0);

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

#endif // AutoComputeTimeSeries_H
