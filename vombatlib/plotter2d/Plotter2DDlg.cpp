

#include "Plotter2DDlg.h"
#include <ui_maindialog.h>

#include <qcustomplot.h>
#include <ccoutofcore/ccTimeSeries.h>
#include <boost/foreach.hpp>

#include "PropertyInspector.h"
#include <plotter2d/CustomPlotWidget.h>

#include <QToolBar>
#include <QDockWidget>
#include <spc/methods/TimeSeriesBandPassFilter.h>

Q_DECLARE_METATYPE(QCPScatterStyle)



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
    //	m_manager = new QtVariantPropertyManager(this);

    //	connect(m_manager,
    //            SIGNAL(valueChanged(QtProperty *, const QVariant &)), this,
    //            SLOT(valueChanged(QtProperty *, const QVariant &)));


    QDockWidget *dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, dock);


    PropertyBrowser *browser = new PropertyBrowser(dock);
    m_browser = browser;
    dock->setWidget(m_browser);

    spc::TimeSeriesBandPassFilter::Ptr  bandpass (new spc::TimeSeriesBandPassFilter);
    GenericFilterQt * f =new GenericFilterQt(bandpass, this);
    this->addFilter(f);

    LOG(INFO) << "added bandpass filter " ;


    //	QtVariantEditorFactory *factory = new QtVariantEditorFactory(this);
    //	m_browser->setFactoryForManager(m_manager, factory);




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

void Plotter2DDlg::handleNewSeries(ccTimeSeries *serie)
{
    getCurrentPlotWidget()->addSeries(serie);
}

void Plotter2DDlg::selected(CustomPlotWidget *plot)
{
    m_last_plot = plot;
    selectionChanged();
}

QList<QObject *> Plotter2DDlg::getCurrentlySelectedObjects()
{

    if (m_last_plot == NULL)
        return QList<QObject *> (); // empty list

    QList<QObject *> obj_list;

    QList<QCPAxis * >sel_axis = m_last_plot->selectedAxes();
    QList<QCPGraph *> graphs = m_last_plot->selectedGraphs();
    QList<QCPAbstractItem *> items = m_last_plot->selectedItems();

    QList<QCPLegend *> legends = m_last_plot->selectedLegends();
    QList<QCPAbstractPlottable *> plottables = m_last_plot->selectedPlottables();


    for (QObject * ob: sel_axis)
        obj_list.append(ob);

    for (QObject * ob: items)
        obj_list.append(ob);

    for (QObject * ob: legends)
        obj_list.append(ob);

    for (QObject * ob: graphs)
        obj_list.append(ob);

    for (QObject * ob: plottables)
        obj_list.append(ob);

    return obj_list;
}

QList<ccHObject *> Plotter2DDlg::getCurrentlySelectedCCHObjects()
{

    QList<ccHObject *> out;
    QList<QObject *> obj_list = getCurrentlySelectedObjects();

    QList<QCPLayerable *> asl;
    for (auto i: obj_list)
    {
        QCPLayerable * l = dynamic_cast<QCPLayerable *> (i);

        if (l)
        {
            ccHObject * o = m_last_plot->layerableToObject(l);
            if (o)
            {
                out.push_back(o);
            }
        }
    }

    return out;

}

void Plotter2DDlg::clearCurrentPlot()
{
    if (m_last_plot) {
        m_last_plot->clearPlot();
    }
}

void Plotter2DDlg::selectionChanged()
{
    QList<QObject *> selected = getCurrentlySelectedObjects();
    if (selected.size() > 0)
        m_browser->setObject(selected.at(0));
    else
        m_browser->setObject(NULL);

    LOG(INFO) << "selection changed";


    updatedSelectionInFilters();


    updateActiveFilters();
}

void Plotter2DDlg::updateActiveFilters()
{

    LOG(INFO) << "Updating active filters";

    for (GenericFilterQt * f: filters_)
    {
        if (f->canCompute())
        {
            LOG(INFO) << "enabling";
            filters_to_actions[f]->setEnabled(true);
        }
        else
        {
            LOG(INFO) << "disabling";
            filters_to_actions[f]->setEnabled(false);
        }

    }

    LOG(INFO) << "done";
}

void Plotter2DDlg::addFilter(GenericFilterQt *filter)
{

    if(std::find(filters_.begin(), filters_.end(), filter) != filters_.end())
        return;

    QAction * action = new QAction(this);
    action->setText(filter->getFilterName());

    this->ui->toolBar->addAction(action);


    connect(filter, SIGNAL(activated(GenericFilterQt *)), this, SLOT(setActiveFilter(GenericFilterQt *)));

    // connect this  action with
    connect(action, SIGNAL(triggered(bool)), filter, SLOT(activate(bool)));

    connect (this, SIGNAL(selectionChanged), this, SLOT(updatedSelectionInFilters));

    filters_to_actions[filter] = action;

    filters_.push_back(filter);

}

void Plotter2DDlg::updatedSelectionInFilters()
{

    LOG(INFO) << "Updating the selection in filters";
    QList<ccHObject *> list = getCurrentlySelectedCCHObjects();

    QList<QObject *> good;

    for (ccHObject * obj: list)
    {
        QObject * asqobj = dynamic_cast<QObject *> (obj);
        if (asqobj)
            good.push_back(asqobj);
    }

    for (GenericFilterQt * f: filters_)
        f->setCurrentSelection(good);
}

void Plotter2DDlg::setActiveFilter(GenericFilterQt * f)
{

    LOG(INFO) << "setting active filter " << f;
    active_filter_ = f;


    this->showFilterOptions();

}



void Plotter2DDlg::showFilterOptions()
{
    if (active_filter_)
        m_browser->setObject(active_filter_);
}


















//void Plotter2DDlg::updateProperties(QList<QCPGraph *> graphs)
//{
//	m_browser->clear();

//    if (graphs.size() > 1) // only one at a time please
//        return;

//    QMap<QtProperty *, QString>::ConstIterator itProp
//        = propertyToId.constBegin();
//    while (itProp != propertyToId.constEnd()) {
//        delete itProp.key();
//        itProp++;
//    }

//    if (graphs.empty()) {
//        propertyToId.clear();
//        idToProperty.clear();
//		m_object = 0;
//        return;
//    }

//    /////////////////////////////////////////////////

//    QCPGraph *graph = graphs.at(0); // only the first one for now

//    propertyToId.clear();
//    idToProperty.clear();

//	m_object = graph;

//    ///////////////////////////////// LINE STYLE
//    QtVariantProperty *property;

//	property = m_manager->addProperty(
//        QtVariantPropertyManager::enumTypeId(), tr("Line Style"));

//    QMetaObject meta = QCPGraph::staticMetaObject;
//    int index = meta.indexOfEnumerator("LineStyle");

//    QMetaEnum metaEnum = meta.enumerator(index);
//    QStringList names;
//    for (int i = 0; i < metaEnum.keyCount(); ++i) {
//        QString name = metaEnum.valueToKey(i);
//        names.push_back(name);
//    }

//    property->setAttribute("enumNames", names);
//    property->setValue((int)graph->lineStyle()); // "Suggestion"

//    addProperty(property, "Line Style");

//    ///////////////////////////////// LINE SIZE
//    QtVariantProperty *property2;

//	property2 = m_manager->addProperty(QVariant::Double, tr("Line Width"));

//    property->setAttribute("minimum", 0.0);
//    property2->setValue(graph->pen().widthF()); // current value
//    addProperty(property2, "Line Width");

//    /////////////////////////////////////// SCATTER SHAPE

//    QtVariantProperty *property3;

//	property3 = m_manager->addProperty(
//        QtVariantPropertyManager::enumTypeId(), tr("Scatter Shape"));

//    meta = QCPScatterStyle::staticMetaObject;
//    index = meta.indexOfEnumerator("ScatterShape");

//    metaEnum = meta.enumerator(index);
//    names.clear();
//    for (int i = 0; i < metaEnum.keyCount(); ++i) {
//        QString name = metaEnum.valueToKey(i);
//        names.push_back(name);
//    }

//    property3->setAttribute("enumNames", names);
//    property3->setValue((int)graph->scatterStyle().shape()); // "Suggestion"

//    addProperty(property3, "Scatter Shape");
//}

void Plotter2DDlg::itemClicked(ccTimeSeries *item)
{
    std::cout << "item clicked" << std::endl;
}

//void Plotter2DDlg::addProperty(QtVariantProperty *property, const QString &id)
//{
//    propertyToId[property] = id;
//    idToProperty[id] = property;
//	QtBrowserItem *item = m_browser->addProperty(property);
//    //    if (idToExpanded.contains(id))
//    //        propertyEditor->setExpanded(item, idToExpanded[id]);
//}

//void Plotter2DDlg::valueChanged(QtProperty *property, const QVariant &value)
//{
//    if (!propertyToId.contains(property))
//        return;

//	if (!m_object)
//        return;

//    QString id = propertyToId[property];

//    if (id == "Line Style") {
//		m_object->setLineStyle((QCPGraph::LineStyle)value.toInt());
//        this->getCurrentPlotWidget()->replot();

//    } else if (id == "Scatter Shape") {
//		QCPScatterStyle prev_style = m_object->scatterStyle();
//        prev_style.setShape((QCPScatterStyle::ScatterShape)value.toInt());
//		m_object->setScatterStyle(prev_style);
//        this->getCurrentPlotWidget()->replot();

//    } else if (id == "Line Width") {
//		QPen old = m_object->pen();
//        old.setWidthF(value.toDouble());
//		m_object->setPen(old);
//        this->getCurrentPlotWidget()->replot();
//    }
//}

CustomPlotWidget *Plotter2DDlg::getCurrentPlotWidget()
{
    DLOG(INFO) <<"last plot:" << m_last_plot;

    if (!m_last_plot) {
        DLOG(WARNING) << "last plot not present , adding one";
        CustomPlotWidget *plot = this->addNewPlot();
        return plot;
    }

    return m_last_plot;
}


void Plotter2DDlg::handleNewSample(ccSample *sample)
{
    DLOG(INFO) << "Handling new sample";
    getCurrentPlotWidget()->addSample(sample);



}
