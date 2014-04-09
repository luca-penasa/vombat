#ifndef VOMBAT_PLOTTER2D_HEADER
#define VOMBAT_PLOTTER2D_HEADER

#include <QDialog>



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
    void addPlot(ccTimeSeries * series);




protected:

    virtual void dropEvent(QDropEvent *de);
    void dragMoveEvent(QDragMoveEvent *de);
    void dragEnterEvent(QDragEnterEvent *event);



    bool isYetPlotted(ccTimeSeries * ser);

    QCustomPlot * getPlotWidget() const;


    Ui::Plotter2DDlgUi * ui;

    std::vector<ccTimeSeries *> all_series_;


};









#endif

