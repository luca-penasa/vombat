#ifndef SENDTO2DPLOT_H
#define SENDTO2DPLOT_H
#include <BaseFilter.h>


class SendTo2DPlot: public BaseFilter
{
public:
    SendTo2DPlot(ccPluginInterface * parent_plugin = 0);

    virtual int compute();

protected:
    virtual int checkSelected();




};

#endif // SENDTO2DPLOT_H
