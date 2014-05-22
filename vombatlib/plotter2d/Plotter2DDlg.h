#ifndef VOMBAT_PLOTTER2D_HEADER
#define VOMBAT_PLOTTER2D_HEADER

class ccTimeSeries;
class CustomPlotWidget;

#include <iostream>
#include <PropertyInspector.h>
#include <QMainWindow>
#include <QMdiSubWindow>
namespace Ui
{
class maindialog;
}

//// te dialog with the widgt collecting the plots
class Plotter2DDlg : public QMainWindow
{
    Q_OBJECT


public:
    Plotter2DDlg(QWidget *parent=0);

    CustomPlotWidget *getCurrentPlotWidget();
public slots:
    CustomPlotWidget *addNewPlot();

    void handleNewPlot(ccTimeSeries * serie);


    void closedSubPlot(CustomPlotWidget * plot)
    {
        if (m_last_plot == plot)
            m_last_plot =0;
    }

    void selected(CustomPlotWidget * plot);



    void clearCurrentPlot();

signals:
    void activated(CustomPlotWidget * plot);


protected:
    Ui::maindialog * ui;

    PropertyBrowser *property_browser;

    CustomPlotWidget * m_last_plot;





};









#endif

