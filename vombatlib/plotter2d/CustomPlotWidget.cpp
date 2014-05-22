#include "plotter2d/CustomPlotWidget.h"
#include <ccoutofcore/ccTimeSeries.h>
CustomPlotWidget::CustomPlotWidget(QWidget *parent): QCustomPlot(parent)
{
    this->setInteractions(QCP::iRangeZoom |QCP::iRangeDrag | QCP::iSelectPlottables | QCP::iSelectAxes );
    connect(this, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));


}

CustomPlotWidget::~CustomPlotWidget()
{
    emit closed(this);
}

bool CustomPlotWidget::isYetPlotted(ccTimeSeries *ser)
{
    spcForEachMacro(ccTimeSeries * se,all_series_)
    {
        if (ser == se)
            return true;
    }

    return false;
}

int CustomPlotWidget::addPlot(ccTimeSeries *series, const QCPGraph::LineStyle &lstyle, const QCPScatterStyle::ScatterShape &scatterShape)
{

    std::cout << "beginning" << std::endl;

        std::cout << "serie: " << series << std::endl;
    series->setLocked(true); // we lock the series so that the user cannot delete it!

    all_series_.push_back(series);

    QVector<double> x = series->getX();
    QVector<double> y = series->getY();

    QCPGraph * graph = this->addGraph();


    QPen graphPen;
    graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
    graph->setPen(graphPen);

    graph->setLineStyle(lstyle);
    graph->setScatterStyle(QCPScatterStyle(scatterShape));

    graph->setData(x, y);
    this->rescaleAxes(true);

    this->replot();
    emit seriesAdded(series);

    return all_series_.size() - 1;
}

void CustomPlotWidget::clearPlot()
{
    this->clearGraphs();

    for (int i = 0 ; i < all_series_.size(); ++i)
    {
        all_series_.at(i)->setLocked(false); //unlock series
    }
    all_series_.clear();
    this->replot();
}

void CustomPlotWidget::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeZoom(this->xAxis->orientation());
    else if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeZoom(this->yAxis->orientation());
    else
        this->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}
