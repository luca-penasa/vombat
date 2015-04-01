#ifndef VOMBAT_PLOTTER2D_HEADER
#define VOMBAT_PLOTTER2D_HEADER

class ccTimeSeries;
class CustomPlotWidget;
class ccSample;

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

	void addClassProperties(const QMetaObject *metaObject);
	void updateClassProperties(const QMetaObject *metaObject, bool recursive);
	void saveExpandedState();
	void restoreExpandedState();
	int enumToInt(const QMetaEnum &metaEnum, int enumValue) const;
	int intToEnum(const QMetaEnum &metaEnum, int intValue) const;
	int flagToInt(const QMetaEnum &metaEnum, int flagValue) const;
	int intToFlag(const QMetaEnum &metaEnum, int intValue) const;
	bool isSubValue(int value, int subValue) const;
	bool isPowerOf2(int value) const;

	void setObject(QObject *object);


	CustomPlotWidget *getCurrentPlotWidget();
//    void addProperty(QtVariantProperty *property, const QString &id);
public slots:

	void slotValueChanged(QtProperty *property, const QVariant &value);

    CustomPlotWidget *addNewPlot();

	void handleNewSeries(ccTimeSeries * serie);

	void handleNewSample(ccSample * sample);

    void closedSubPlot(CustomPlotWidget * plot)
    {
        if (m_last_plot == plot)
            m_last_plot = 0;
    }

    void selected(CustomPlotWidget * plot);

    QList<class QCPGraph *> getCurrentlySelectedGraphs();

    void clearCurrentPlot();

    void selectionChanged();

//    void updateProperties(QList<QCPGraph *> graph);

signals:
    void activated(CustomPlotWidget * plot);

private slots:
    void itemClicked(ccTimeSeries *item);
//    void valueChanged(QtProperty *property, const QVariant &value);


protected:
    Ui::maindialog * ui;

//    PropertyBrowser *m_browser;

    CustomPlotWidget * m_last_plot;

	class QtVariantPropertyManager *m_manager;
	PropertyBrowser    *m_browser;
//	QtVariantPropertyManager *m_manager;
	class QtVariantPropertyManager *m_readOnlyManager;


//    QMap<QtProperty *, QString> propertyToId;
//    QMap<QString, QtVariantProperty *> idToProperty;
//    QMap<QString, bool> idToExpanded;

	class QObject * m_object;

	QMap<const QMetaObject *, QtProperty *> m_classToProperty;
	QMap<QtProperty *, const QMetaObject *> m_propertyToClass;
	QMap<QtProperty *, int>     m_propertyToIndex;

	QMap<const QMetaObject *, QMap<int, QtVariantProperty *> > m_classToIndexToProperty;

	QMap<QtProperty *, bool>    m_propertyToExpanded;
	QList<QtProperty *>         m_topLevelProperties;






};









#endif

