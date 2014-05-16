


#include "Plotter2DDlg.h"
#include <plotter2d/ui_Plotter2DDlg.h>

#include <external/qcustomplot.h>
#include <ccoutofcore/ccTimeSeries.h>
#include <boost/foreach.hpp>


#include <QToolBar>

Plotter2DDlg::Plotter2DDlg(QWidget *parent): QDialog(parent), ui(new Ui::Plotter2DDlgUi)
{

    ui->setupUi(this);


    QToolBar *tbar  = new QToolBar(this);
    this->ui->verticalLayout->addWidget(tbar);

//    tbar->addAction(this->ui->actionExport);
//    tbar->addAction(this->ui->actionSaveTimeSeries);
    tbar->addAction(this->ui->actionClearPlot);


    ui->plot->setInteractions(QCP::iRangeZoom |QCP::iRangeDrag | QCP::iSelectPlottables | QCP::iSelectAxes );
    connect(ui->plot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    connect(ui->actionClearPlot, SIGNAL(triggered()), this, SLOT(clearPlots()));

    this->ui->plot->setAcceptDrops(true);
}

void Plotter2DDlg::addPlot(ccTimeSeries *series)
{
    if (isYetPlotted(series))
        return;

    series->setLocked(true); // we lock the series so that the user cannot delete it!

    all_series_.push_back(series);

    //add the graph
    QCustomPlot * plot = getPlotWidget();

    QVector<double> x = series->getX();
    QVector<double> y = series->getY();

    QCPGraph * graph = plot->addGraph();
    graph->setData(x, y);
    plot->rescaleAxes(true);

    plot->replot();
    emit seriesAdded(series);
}

void Plotter2DDlg::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->plot->axisRect()->setRangeZoom(ui->plot->xAxis->orientation());
    else if (ui->plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->plot->axisRect()->setRangeZoom(ui->plot->yAxis->orientation());
    else
        ui->plot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void Plotter2DDlg::clearPlots()
{
    ui->plot->clearGraphs();

    for (int i = 0 ; i < all_series_.size(); ++i)
    {
        all_series_.at(i)->setLocked(false); //unlock series
    }
    all_series_.clear();
    ui->plot->replot();
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
