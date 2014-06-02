#include "SendTo2DPlot.h"
#include <vombat.h>
#include <plotter2d/Plotter2DDlg.h>
#include <ccoutofcore/ccTimeSeries.h>

#include <plotter2d/CustomPlotWidget.h>

SendTo2DPlot::SendTo2DPlot(ccPluginInterface *parent_plugin): BaseFilter(FilterDescription(   "Send the TS to 2d Plotter",
                                                                                              "Send the TS to 2d Plotter",
                                                                                              "Send the TS to 2d Plotter",
                                                                                              ":/toolbar/icons/plot.png"), parent_plugin)
{
    this->setShowProgressBar(false);
}



int SendTo2DPlot::compute()
{
    // ensure we are connected
    this->connectToPlotter();

    ccHObject * selected = getSelectedEntityAsCCHObject();

    //    selected->setLocked(true);

    ccTimeSeries * serie = static_cast<ccTimeSeries *> (selected);
    if (!serie)
        return -1;

    Plotter2DDlg * plot =  vombat::theInstance()->getPlotter2DDlg();

    emit handleNewPlot(serie);

    return 1;
}




int SendTo2DPlot::checkSelected()
{
    ccHObject * selected = getSelectedEntityAsCCHObject();
    if (selected && selected->getMetaData("class_name") == "ccTimeSeries")
        return 1;
    else
        return 0;
}

void SendTo2DPlot::connectToPlotter()
{
    connect(this, SIGNAL(handleNewPlot(ccTimeSeries*)), (vombat::theInstance()->getPlotter2DDlg()), SLOT(handleNewPlot(ccTimeSeries * )));
}
