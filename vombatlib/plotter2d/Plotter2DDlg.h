#ifndef VOMBAT_PLOTTER2D_HEADER
#define VOMBAT_PLOTTER2D_HEADER

class ccTimeSeries;
class CustomPlotWidget;
class ccSample;


#include <iostream>
#include <PropertyInspector.h>
#include <QMainWindow>
#include <QMdiSubWindow>

#include <GenericFilterQt.h>
#include <ccHObject.h>
namespace Ui
{
class maindialog;
}

class QCPAbstractItem;

//// te dialog with the widgt collecting the plots
class Plotter2DDlg : public QMainWindow
{
    Q_OBJECT

public:
    Plotter2DDlg(QWidget *parent=0);

    ~Plotter2DDlg()
    {

    }




	CustomPlotWidget *getCurrentPlotWidget();
//    void addProperty(QtVariantProperty *property, const QString &id);
public slots:


    CustomPlotWidget *addNewPlot();

	void handleNewSeries(ccTimeSeries * serie);

	void handleNewSample(ccSample * sample);

    void closedSubPlot(CustomPlotWidget * plot)
    {
        if (m_last_plot == plot)
            m_last_plot = 0;
    }

    void selected(CustomPlotWidget * plot);

	QList<QObject *> getCurrentlySelectedObjects();

    QList<ccHObject *> getCurrentlySelectedCCHObjects();

    void clearCurrentPlot();

    void selectionChanged();

    void updateActiveFilters();

    void addFilter(GenericFilterQt * filter);

    void updatedSelectionInFilters();

    void setActiveFilter(GenericFilterQt * f);

    void showFilterOptions();

//    void updateProperties(QList<QCPGraph *> graph);

signals:
    void activated(CustomPlotWidget * plot);

private slots:
    void itemClicked(ccTimeSeries *item);
//    void valueChanged(QtProperty *property, const QVariant &value);


protected:
    Ui::maindialog * ui;

    std::vector<GenericFilterQt *> filters_;

//    PropertyBrowser *m_browser;

    CustomPlotWidget * m_last_plot;

	PropertyBrowser    *m_browser;
//	QtVariantPropertyManager *m_manager;


    GenericFilterQt * active_filter_ = nullptr;

    QMap<GenericFilterQt *, QAction *> filters_to_actions;
};









#endif

