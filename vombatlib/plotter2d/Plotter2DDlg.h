#ifndef VOMBAT_PLOTTER2D_HEADER
#define VOMBAT_PLOTTER2D_HEADER

#include <QDialog>
#include <external/qcustomplot.h>


class QCPAxis;
class QCustomPlot;
class ccTimeSeries;




namespace Ui
{
class Plotter2DDlgUi;
}

//// te dialog with the widgt collecting the plots
class Plotter2DDlg : public QDialog
{
    Q_OBJECT
public:
    Plotter2DDlg(QWidget *parent=0);

signals:
    ///every time a ts is plottet this will be emitted
    void seriesAdded(ccTimeSeries * series);

public slots:

    //! it returns the index of the added series into the all_series_ vector
    int addPlot(ccTimeSeries * series,
                const QCPGraph::LineStyle & lstyle = QCPGraph::lsLine,
                const QCPScatterStyle::ScatterShape &scatterShape = QCPScatterStyle::ssNone);

    //! called when mouse wheel is wheeled :-)
    void mouseWheel();

    //! clear everything into the plot
    void clearPlots();


protected:

    virtual void dropEvent(QDropEvent *de);
    void dragMoveEvent(QDragMoveEvent *de);
    void dragEnterEvent(QDragEnterEvent *event);


    //! is this series yet present?
    bool isYetPlotted(ccTimeSeries * ser);





    QCustomPlot * getPlotWidget() const;


    Ui::Plotter2DDlgUi * ui;

    std::vector<ccTimeSeries *> all_series_;




};









#endif

