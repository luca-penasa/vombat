#ifndef VOMBAT_PLOTTER2D_HEADER
#define VOMBAT_PLOTTER2D_HEADER

class ccTimeSeries;
class CustomPlotWidget;

#include <iostream>
#include <PropertyInspector.h>
#include <QMainWindow>
#include <QMdiSubWindow>
#include <qtvariantproperty.h>



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

    ~Plotter2DDlg()
    {

    }

    CustomPlotWidget *getCurrentPlotWidget();
    void addProperty(QtVariantProperty *property, const QString &id);
public slots:
    CustomPlotWidget *addNewPlot();

    void handleNewPlot(ccTimeSeries * serie);

    void closedSubPlot(CustomPlotWidget * plot)
    {
        if (m_last_plot == plot)
            m_last_plot = 0;
    }

    void selected(CustomPlotWidget * plot);

    QList<class QCPGraph *> getCurrentlySelectedGraphs();

    void clearCurrentPlot();

    void selectionChanged();

    void updateProperties(QList<QCPGraph *> graph);

signals:
    void activated(CustomPlotWidget * plot);

private slots:
    void itemClicked(ccTimeSeries *item);
    void valueChanged(QtProperty *property, const QVariant &value);


protected:
    Ui::maindialog * ui;

    PropertyBrowser *propertyEditor;

    CustomPlotWidget * m_last_plot;

    class QtVariantPropertyManager *variantManager;

    QMap<QtProperty *, QString> propertyToId;
    QMap<QString, QtVariantProperty *> idToProperty;
    QMap<QString, bool> idToExpanded;

    class QCPGraph * currentItem;

};









#endif

