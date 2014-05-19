#include "SendTo2DPlot.h"
#include <vombat.h>
#include <plotter2d/Plotter2DDlg.h>
#include <ccoutofcore/ccTimeSeries.h>

SendTo2DPlot::SendTo2DPlot(ccPluginInterface *parent_plugin): BaseFilter(FilterDescription(   "Send the TS to 2d Plotter",
                                                                                              "Send the TS to 2d Plotter",
                                                                                              "Send the TS to 2d Plotter",
                                                                                              ":/toolbar/icons/plot.png"), parent_plugin)
{
    this->setShowProgressBar(false);
}



int SendTo2DPlot::compute()
{
    ccHObject * selected = getSelectedEntityAsCCHObject();

    //    selected->setLocked(true);

    ccTimeSeries * serie = static_cast<ccTimeSeries *> (selected);
    if (!serie)
        return -1;

    // now get line style
    QCPGraph::LineStyle lstyle = m_dialog->getLineStyle();

    QCPScatterStyle::ScatterShape scatterShape = m_dialog->getScatterShape();


    Plotter2DDlg * plot =  vombat::theInstance()->getPlotter2DDlg();



    plot->addPlot(serie, lstyle, scatterShape);

    return 1;
}




int SendTo2DPlot::checkSelected()
{
    ccHObject * selected = getSelectedEntityAsCCHObject();
    if (selected && selected->hasMetaData("[vombat][ccTimeSeries]"))
        return 1;
    else
        return 0;
}
