#pragma once
#ifndef SENDTO2DPLOT_H
#define SENDTO2DPLOT_H
#include "BaseFilter.h"

class ccTimeSeries;
class ccSample;

class SendTo2DPlot : public BaseFilter {
    Q_OBJECT // so we can have signals
public:
    SendTo2DPlot(ccPluginInterface* parent_plugin = 0);

    ~SendTo2DPlot()
    {
    }

    virtual int compute();

signals:
    void handleNewSeries(ccTimeSeries* serie);

    void handleNewSample(ccSample* sample);

protected:
    virtual int checkSelected();

    void connectToPlotter();
};

#endif // SENDTO2DPLOT_H
