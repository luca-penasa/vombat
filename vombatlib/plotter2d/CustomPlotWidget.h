#ifndef VOMBAT_CUSTOMPLOTWIDGET_H
#define VOMBAT_CUSTOMPLOTWIDGET_H

#include <external/qcustomplot.h>
#include <plotter2d/Plotter2DDlg.h>
#include <QMdiArea>
class ccTimeSeries;
class QWidget;
class QCPAxis;

//// main plot widget
class CustomPlotWidget : public QCustomPlot
{
    Q_OBJECT

protected:
    std::vector<ccTimeSeries *> all_series_;

public:
    explicit CustomPlotWidget(QWidget *parent);
    ~CustomPlotWidget();

    //! is this series yet present?
    bool isYetPlotted(ccTimeSeries * ser);

signals:
    ///every time a ts is plottet this will be emitted
    void seriesAdded(ccTimeSeries * series);

    void activated(CustomPlotWidget * plot);

    void closed(CustomPlotWidget * plot);



public slots:
    //! called when mouse wheel is wheeled :-)
    void mouseWheel();

    void imActive()
    {
        emit activated(this);
    }




    //! it keeps a ptr to the added series into the all_series_ vector
    int addPlot(ccTimeSeries * series,
                const QCPGraph::LineStyle & lstyle = QCPGraph::lsLine,
                const QCPScatterStyle::ScatterShape &scatterShape = QCPScatterStyle::ssCrossCircle);

    //! clear everything into the plot
    void clearPlot();

    QList<QCPGraph * > getCurrentlySelectedGraphs()
    {
        return this->selectedGraphs();
    }



};


#endif // CUSTOMPLOTWIDGET_H
