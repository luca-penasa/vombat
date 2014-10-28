

#include "Plotter2DDlg.h"
#include <ui_maindialog.h>

#include <qcustomplot.h>
#include <ccoutofcore/ccTimeSeries.h>
#include <boost/foreach.hpp>

#include "PropertyInspector.h"
#include <plotter2d/CustomPlotWidget.h>

#include <QToolBar>

Plotter2DDlg::Plotter2DDlg(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::maindialog), m_last_plot()
{

    ui->setupUi(this);

    connect(ui->actionNewPlot, SIGNAL(triggered()), this, SLOT(addNewPlot()));
    connect(ui->actionClearPlot, SIGNAL(triggered()), this,
            SLOT(clearCurrentPlot()));
    //    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this,
    // SLOT(setSelected(CustomPlotWidget*)));

    // properties brower
    variantManager = new QtVariantPropertyManager(this);

    connect(variantManager,
            SIGNAL(valueChanged(QtProperty *, const QVariant &)), this,
            SLOT(valueChanged(QtProperty *, const QVariant &)));

    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);

    QDockWidget *dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    propertyEditor = new PropertyBrowser(dock);

    propertyEditor->setFactoryForManager(variantManager, variantFactory);
    dock->setWidget(propertyEditor);

    currentItem = 0;
}

CustomPlotWidget *Plotter2DDlg::addNewPlot()
{

    CustomPlotWidget *plot = new CustomPlotWidget(this);

    m_last_plot = plot;
    QMdiSubWindow *swin = this->ui->mdiArea->addSubWindow(plot);
    swin->setAttribute(Qt::WA_DeleteOnClose);

    swin->show();

    // each plot will notify when destroyed
    connect(plot, SIGNAL(closed(CustomPlotWidget *)), this,
            SLOT(closedSubPlot(CustomPlotWidget *)));

    // subwindows must notify themselves when selected
    connect(swin, SIGNAL(aboutToActivate()), plot, SLOT(imActive()));
    connect(plot, SIGNAL(activated(CustomPlotWidget *)), this,
            SLOT(selected(CustomPlotWidget *)));
    connect(plot, SIGNAL(selectionChangedByUser()), this,
            SLOT(selectionChanged()));
    return plot;
}

void Plotter2DDlg::handleNewPlot(ccTimeSeries *serie)
{
    getCurrentPlotWidget()->addPlot(serie);
}

void Plotter2DDlg::selected(CustomPlotWidget *plot)
{
    m_last_plot = plot;
    selectionChanged();
}

QList<QCPGraph *> Plotter2DDlg::getCurrentlySelectedGraphs()
{
    if (m_last_plot)
        return m_last_plot->getCurrentlySelectedGraphs();
}

void Plotter2DDlg::clearCurrentPlot()
{
    if (m_last_plot) {
        m_last_plot->clearPlot();
    }
}

void Plotter2DDlg::selectionChanged()
{

    updateProperties(getCurrentlySelectedGraphs());
}

void Plotter2DDlg::updateProperties(QList<QCPGraph *> graphs)
{
    propertyEditor->clear();

    if (graphs.size() > 1) // only one at a time please
        return;

    QMap<QtProperty *, QString>::ConstIterator itProp
        = propertyToId.constBegin();
    while (itProp != propertyToId.constEnd()) {
        delete itProp.key();
        itProp++;
    }

    if (graphs.empty()) {
        propertyToId.clear();
        idToProperty.clear();
        currentItem = 0;
        return;
    }

    /////////////////////////////////////////////////

    QCPGraph *graph = graphs.at(0); // only the first one for now

    propertyToId.clear();
    idToProperty.clear();

    currentItem = graph;

    ///////////////////////////////// LINE STYLE
    QtVariantProperty *property;

    property = variantManager->addProperty(
        QtVariantPropertyManager::enumTypeId(), tr("Line Style"));

    QMetaObject meta = QCPGraph::staticMetaObject;
    int index = meta.indexOfEnumerator("LineStyle");

    QMetaEnum metaEnum = meta.enumerator(index);
    QStringList names;
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        QString name = metaEnum.valueToKey(i);
        names.push_back(name);
    }

    property->setAttribute("enumNames", names);
    property->setValue((int)graph->lineStyle()); // "Suggestion"

    addProperty(property, "Line Style");

    ///////////////////////////////// LINE SIZE
    QtVariantProperty *property2;

    property2 = variantManager->addProperty(QVariant::Double, tr("Line Width"));

    property->setAttribute("minimum", 0.0);
    property2->setValue(graph->pen().widthF()); // current value
    addProperty(property2, "Line Width");

    /////////////////////////////////////// SCATTER SHAPE

    QtVariantProperty *property3;

    property3 = variantManager->addProperty(
        QtVariantPropertyManager::enumTypeId(), tr("Scatter Shape"));

    meta = QCPScatterStyle::staticMetaObject;
    index = meta.indexOfEnumerator("ScatterShape");

    metaEnum = meta.enumerator(index);
    names.clear();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        QString name = metaEnum.valueToKey(i);
        names.push_back(name);
    }

    property3->setAttribute("enumNames", names);
    property3->setValue((int)graph->scatterStyle().shape()); // "Suggestion"

    addProperty(property3, "Scatter Shape");
}

void Plotter2DDlg::itemClicked(ccTimeSeries *item)
{
    std::cout << "item clicked" << std::endl;
}

void Plotter2DDlg::addProperty(QtVariantProperty *property, const QString &id)
{
    propertyToId[property] = id;
    idToProperty[id] = property;
    QtBrowserItem *item = propertyEditor->addProperty(property);
    //    if (idToExpanded.contains(id))
    //        propertyEditor->setExpanded(item, idToExpanded[id]);
}

void Plotter2DDlg::valueChanged(QtProperty *property, const QVariant &value)
{
    if (!propertyToId.contains(property))
        return;

    if (!currentItem)
        return;

    QString id = propertyToId[property];

    if (id == "Line Style") {
        currentItem->setLineStyle((QCPGraph::LineStyle)value.toInt());
        this->getCurrentPlotWidget()->replot();

    } else if (id == "Scatter Shape") {
        QCPScatterStyle prev_style = currentItem->scatterStyle();
        prev_style.setShape((QCPScatterStyle::ScatterShape)value.toInt());
        currentItem->setScatterStyle(prev_style);
        this->getCurrentPlotWidget()->replot();

    } else if (id == "Line Width") {
        QPen old = currentItem->pen();
        old.setWidthF(value.toDouble());
        currentItem->setPen(old);
        this->getCurrentPlotWidget()->replot();
    }
}

CustomPlotWidget *Plotter2DDlg::getCurrentPlotWidget()
{
    std::cout << "getting current plot" << m_last_plot << std::endl;

    if (!m_last_plot) {
        std::cout << "last plot not present , adding one" << std::endl;
        CustomPlotWidget *plot = this->addNewPlot();
        return plot;
    }

    return m_last_plot;
}
