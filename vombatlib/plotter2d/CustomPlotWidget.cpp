#include "plotter2d/CustomPlotWidget.h"
#include <ccoutofcore/ccTimeSeries.h>
#include <ccHObject.h>
#include <ccSample.h>
#include "QCPItemSample.h"
CustomPlotWidget::CustomPlotWidget(QWidget *parent) : QCustomPlot(parent)
{
    this->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag
						  | QCP::iSelectPlottables | QCP::iSelectOther| QCP::iSelectItems | QCP::iSelectAxes);
    connect(this, SIGNAL(mouseWheel(QWheelEvent *)), this, SLOT(mouseWheel()));
}

CustomPlotWidget::~CustomPlotWidget()
{
    emit closed(this);
}

bool CustomPlotWidget::isYetPlotted(ccHObject *ser)
{
    return (cc_to_layerable_.find(ser) != cc_to_layerable_.end());
}

ccHObject *CustomPlotWidget::layerableToObject(QCPLayerable * layerable) const
{
    if (layerable_to_cc_.find(layerable) != layerable_to_cc_.end())
        return layerable_to_cc_[layerable];
    else
    {
        LOG(INFO) << "cannot find the right object for this ayerable";
    }
}



int CustomPlotWidget::addSeries(ccTimeSeries *series)
{
    if (isYetPlotted(series))
        return -1;

    series->setLocked(
        true); // we lock the series so that the user cannot delete it!

    QVector<double> x = series->getX(false);
    QVector<double> y = series->getY(false);

    QCPGraph *graph = this->addGraph();

    QPen graphPen;

    graphPen.setColor(
        QColor(rand() % 245 + 10, rand() % 245 + 10, rand() % 245 + 10));
    graphPen.setWidthF(1);
    graph->setPen(graphPen);

    graph->setData(x, y);
    this->rescaleAxes(true);
    this->replot();
    emit seriesAdded(series);

	layerable_to_cc_[graph] = series;
	cc_to_layerable_[series] = graph;

    return 1;
}

int CustomPlotWidget::addSample(ccSample *sample)
{
	if (isYetPlotted(sample))
		return -1;

		QCPItemSample * qcpsample  = new QCPItemSample(sample, this);
		this->addItem(qcpsample);

		this->replot();


		layerable_to_cc_[qcpsample] = sample;
		cc_to_layerable_[sample] = qcpsample;


	return 1;
}


void CustomPlotWidget::clearPlot()
{

	QList<ccHObject *> ser = cc_to_layerable_.keys();

	for (ccHObject *s : ser)
        s->setLocked(false); // unlock series


    // clear the maps
    this->clearGraphs();
	this->clearItems();
    this->replot();

	layerable_to_cc_.clear();
	cc_to_layerable_.clear();
}

void CustomPlotWidget::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be
    // zoomed
    // if no axis is selected, both directions may be zoomed

    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeZoom(this->xAxis->orientation());
    else if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeZoom(this->yAxis->orientation());
    else
        this->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
}


