


#include "Plotter2DDlg.h"
#include <ui_maindialog.h>

#include <external/qcustomplot.h>
#include <ccoutofcore/ccTimeSeries.h>
#include <boost/foreach.hpp>

#include "PropertyInspector.h"
#include <plotter2d/CustomPlotWidget.h>


#include <QToolBar>

Plotter2DDlg::Plotter2DDlg(QWidget *parent): QMainWindow(parent), ui(new Ui::maindialog), m_last_plot()
{

    std::cout << "new" << std::endl;

    ui->setupUi(this);

//    this->addNewPlot(); // one by default

    QDockWidget *dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    property_browser = new PropertyBrowser(dock);


    connect (ui->actionNewPlot, SIGNAL(triggered()), this, SLOT(addNewPlot()));
    connect (ui->actionClearPlot, SIGNAL(triggered()), this, SLOT(clearCurrentPlot()));
//    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(setSelected(CustomPlotWidget*)));

}






CustomPlotWidget *Plotter2DDlg::addNewPlot()
{


    CustomPlotWidget * plot = new CustomPlotWidget(this);

    m_last_plot = plot;
    QMdiSubWindow * swin = this->ui->mdiArea->addSubWindow(plot);
    swin->setAttribute(Qt::WA_DeleteOnClose);

    swin->show();

    // each plot will notify when destroyed
    connect(plot, SIGNAL(closed(CustomPlotWidget*)), this, SLOT(closedSubPlot(CustomPlotWidget*)));

    //subwindows must notify themselves when selected
    connect(swin, SIGNAL(aboutToActivate()), plot, SLOT(imActive()));
    connect(plot, SIGNAL(activated(CustomPlotWidget*)), this, SLOT(selected(CustomPlotWidget*)));

    return plot;
}

void Plotter2DDlg::handleNewPlot(ccTimeSeries * serie)
{
    getCurrentPlotWidget()->addPlot(serie);
}

void Plotter2DDlg::selected(CustomPlotWidget *plot)
{
    m_last_plot = plot;
}

void Plotter2DDlg::clearCurrentPlot()
{
    if (m_last_plot)
    {
        m_last_plot->clearPlot();
    }
}

//void Plotter2DDlg::dropEvent(QDropEvent *de)
//{
//    ccLog::Print("Dropped object in 2d plot");
//}

//void Plotter2DDlg::dragMoveEvent(QDragMoveEvent *de)
//{
//    // The event needs to be accepted here
//    de->accept();
//}

//void Plotter2DDlg::dragEnterEvent(QDragEnterEvent *event)
//{
//    event->acceptProposedAction();
//}





CustomPlotWidget * Plotter2DDlg::getCurrentPlotWidget()
{
    std::cout << "getting current plot" << m_last_plot << std::endl;

    if (!m_last_plot)
    {
        std::cout << "last plot not present , adding one" << std::endl;
        CustomPlotWidget * plot = this->addNewPlot();
        return plot;
    }


    return m_last_plot;
}
