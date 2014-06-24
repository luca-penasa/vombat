#ifndef VOMBAT_CUSTOMPLOTWIDGET_H
#define VOMBAT_CUSTOMPLOTWIDGET_H

#include <qcustomplot.h>
#include <plotter2d/Plotter2DDlg.h>
#include <QMdiArea>
class ccTimeSeries;
class QWidget;
class QCPAxis;

//// main plot widget
class CustomPlotWidget : public QCustomPlot
{
    Q_OBJECT
public:
    explicit CustomPlotWidget(QWidget *parent);
    ~CustomPlotWidget();

    //! is this series yet present?
    bool isYetPlotted(ccTimeSeries *ser);

signals:
    /// every time a ts is plottet this will be emitted
    void seriesAdded(ccTimeSeries *series);

    void activated(CustomPlotWidget *plot);

    void closed(CustomPlotWidget *plot);

public
slots:
    //! called when mouse wheel is wheeled :-)
    void mouseWheel();

    void imActive()
    {
        emit activated(this);
    }

    //! it keeps a ptr to the added series into the all_series_ vector
    int addPlot(ccTimeSeries *series);

    //! clear everything into the plot
    void clearPlot();

    QList<QCPGraph *> getCurrentlySelectedGraphs()
    {
        return this->selectedGraphs();
    }

protected:
    QMap<ccTimeSeries *, QCPGraph *> cc_to_graph_;
    QMap<QCPGraph *, ccTimeSeries *> graph_to_cc_;
};

#endif // CUSTOMPLOTWIDGET_H
