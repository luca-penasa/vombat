#include "SendTo2DPlot.h"
#include <vombat.h>
#include <plotter2d/Plotter2DDlg.h>
#include <ccoutofcore/ccTimeSeries.h>
#include <ccoutofcore/ccSample.h>
#include <vombat.h>


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

	ccTimeSeries * serie = dynamic_cast<ccTimeSeries  *> (selected);
	if (serie)
	{
		emit handleNewSeries(serie);
		return 1;
	}

	ccSample * sample = dynamic_cast<ccSample * > (selected);
	if (sample)
	{
		emit handleNewSample(sample);
		return 1;
	}


	return 0;
}






int SendTo2DPlot::checkSelected()
{
	ccHObject * selected = getSelectedEntityAsCCHObject();
    if (selected && dynamic_cast<ccTimeSeries *> (selected))
        return 1;
	else if (selected && dynamic_cast<ccSample *> (selected))
		return 1;
	else
		return 0;
}

void SendTo2DPlot::connectToPlotter()
{
	connect(this, SIGNAL(handleNewSeries(ccTimeSeries*)), (vombat::theInstance()->getPlotter2DDlg()), SLOT(handleNewSeries(ccTimeSeries * )));
	connect(this, SIGNAL(handleNewSample(ccSample*)), (vombat::theInstance()->getPlotter2DDlg()), SLOT(handleNewSample(ccSample * )));

}


