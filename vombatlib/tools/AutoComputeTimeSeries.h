#pragma once
#ifndef AUTOCOMPUTE_TIME_SERIES_H
#define AUTOCOMPUTE_TIME_SERIES_H

#include "BaseFilter.h"

class ComputeTimeSeriesDlg;

class AutoComputeTimeSeries : public BaseFilter {
public:
    AutoComputeTimeSeries(ccPluginInterface* parent_plugin = 0);

    // BaseFilter interface
public:
    int compute();

protected:
    int checkSelected();

    int openInputDialog();


    ComputeTimeSeriesDlg * m_dialog;
};

#endif // AutoComputeTimeSeries_H
