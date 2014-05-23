#ifndef SENDTO2DPLOT_H
#define SENDTO2DPLOT_H
#include <qPCL/PclUtils/filters/BaseFilter.h>

class ccTimeSeries;

class SendTo2DPlot: public BaseFilter
{
    Q_OBJECT // so we can have signals
public:
    SendTo2DPlot(ccPluginInterface * parent_plugin = 0);

    virtual int compute();


signals:
    void handleNewPlot(ccTimeSeries *serie);

protected:
    virtual int checkSelected();

    void connectToPlotter();

};

#endif // SENDTO2DPLOT_H
