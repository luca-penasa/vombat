


#include "Plotter2DDlg.h"
#include <plotter2d/ui_Plotter2DDlg.h>

#include <visualization/qcustomplot.h>
#include <ccoutofcore/ccTimeSeries.h>
#include <boost/foreach.hpp>


Plotter2DDlg::Plotter2DDlg(QWidget *parent): QDialog(parent), ui(new Ui::Plotter2DDlgUi)
{
    ui->setupUi(this);

    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectAxes );

    this->ui->plot->setAcceptDrops(true);
}

void Plotter2DDlg::addPlot(ccTimeSeries *series)
{
    if (isYetPlotted(series))
        return;
    all_series_.push_back(series);

    //add the graph
    QCustomPlot * plot = getPlotWidget();

    QVector<double> x = series->getX();
    QVector<double> y = series->getY();


    plot->addGraph();
    plot->graph(0)->setData(x, y);
    plot->rescaleAxes(true);


    plot->replot();
    emit seriesAdded(series);
}

void Plotter2DDlg::dropEvent(QDropEvent *de)
{
    ccLog::Print("Dropped object in 2d plot");
}

void Plotter2DDlg::dragMoveEvent(QDragMoveEvent *de)
{
    // The event needs to be accepted here
    de->accept();
}

void Plotter2DDlg::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();

}

bool Plotter2DDlg::isYetPlotted(ccTimeSeries *ser)
{
    BOOST_FOREACH(ccTimeSeries * se,all_series_)
    {
        if (ser == se)
            return true;
    }

    return false;
}



QCustomPlot *Plotter2DDlg::getPlotWidget() const
{
    return ui->plot;
}
