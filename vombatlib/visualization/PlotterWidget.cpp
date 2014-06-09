#include "PlotterWidget.h"
#include "PlotsContainer.h"
#include "SinglePlot.h"
#include <spc/io/time_series_writer.h>
#include <spc/elements/TimeSeriesBase.h>

#include <sstream>


PlotterWidget::PlotterWidget(QWidget *parent): QCustomPlot(parent), m_main_scale(0), m_plots_container(0)
{
    //clear the layout
    plotLayout()->clear(); //clear all

    /// a main scale object at LEFT
    m_main_scale = new  MainScale(this);
    plotLayout()->addElement(0,0,m_main_scale);

    /// an area with plots at RIGHT
    m_plots_container = new PlotsContainer();
    plotLayout()->addElement(0,1, m_plots_container);

    /// a group for aligning graphs
    m_group = new QCPMarginGroup(this);
    getMainAxisRect()->setMarginGroup(QCP::msTop|QCP::msBottom, m_group);

    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectAxes );

//    SinglePlot * sp =  new SinglePlot(this);

//    spc::ContinousValuesLog * log =  new spc::ContinousValuesLog;
//    log->resize(100);
//    for(int i = 0 ; i < log->size(); ++i)
//        log->setValue(i, i);

//    sp->updateDataWith(log);
//    addSinglePlot(sp);

    replot();

}


void PlotterWidget::handleNewTimeSeries(ccTimeSeries * series)
{
    SinglePlot * plot = new SinglePlot(this);

    plot->updateDataWith(series);

    addSinglePlot(plot);
}

void PlotterWidget::saveAllSeries()
{

    QString dir = QFileDialog::getExistingDirectory();

    if (dir.isEmpty())
        return;

    for (int i = 0 ; i < (getPlotContainer()->getNumberOfPlots() ); ++i)
    {

        std::string fname = dir.toStdString() + std::string("/TimeSeries_");

        std::ostringstream stream;
        stream << i ;

        fname += stream.str() + ".txt";

        spc::TimeSeriesWriter writer;
        SinglePlot * plot = getPlotContainer()->getSinglePlot(i);

        ccTimeSeries * ts = plot->getTimeSeries();

        if (!ts)
        {
            std::cout << "NULL POINTER" << std::endl;
            return;
        }


        std::vector<float> x = ts->getTimeSeries()->getX();
        std::vector<float> y = ts->getTimeSeries()->getY();

        for (int i = 0 ; i < ts->getTimeSeries()->getNumberOfSamples(); ++i)
        {
            std::cout << x.at(i) << " " << y.at(i) << std::endl;
        }

        std::cout << "saving time series" << std::endl;

        writer.setInputSeries(ts->getTimeSeries());

        writer.setFilename(fname);

        writer.writeAsciiAsSparse();

    }
}
