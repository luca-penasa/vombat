

#include "Plotter2DDlg.h"
#include <ui_maindialog.h>

#include <qcustomplot.h>
#include <ccoutofcore/ccTimeSeries.h>
#include <boost/foreach.hpp>

#include "PropertyInspector.h"
#include <plotter2d/CustomPlotWidget.h>

#include <QToolBar>

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

    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);

    QDockWidget *dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, dock);


	PropertyBrowser *browser = new PropertyBrowser(dock);
	browser->setRootIsDecorated(true);
	browser->setAlternatingRowColors(true);

	m_browser = browser;


	m_manager = new QtVariantPropertyManager(this);
	m_readOnlyManager = new QtVariantPropertyManager(this);


	m_browser->setFactoryForManager(m_manager, variantFactory);
	dock->setWidget(m_browser);

	m_object = 0;

//	QtVariantEditorFactory *factory = new QtVariantEditorFactory(this);
//	m_browser->setFactoryForManager(m_manager, factory);

	connect(m_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
				this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));


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

	QList<QCPGraph *> selected = getCurrentlySelectedGraphs();
	if (selected.size() > 0)
		setObject(selected.at(0));

	LOG(INFO) << "selection changed";
}


int Plotter2DDlg::enumToInt(const QMetaEnum &metaEnum, int enumValue) const
{
	QMap<int, int> valueMap; // dont show multiple enum values which have the same values
	int pos = 0;
	for (int i = 0; i < metaEnum.keyCount(); i++) {
		int value = metaEnum.value(i);
		if (!valueMap.contains(value)) {
			if (value == enumValue)
				return pos;
			valueMap[value] = pos++;
		}
	}
	return -1;
}

int Plotter2DDlg::intToEnum(const QMetaEnum &metaEnum, int intValue) const
{
	QMap<int, bool> valueMap; // dont show multiple enum values which have the same values
	QList<int> values;
	for (int i = 0; i < metaEnum.keyCount(); i++) {
		int value = metaEnum.value(i);
		if (!valueMap.contains(value)) {
			valueMap[value] = true;
			values.append(value);
		}
	}
	if (intValue >= values.count())
		return -1;
	return values.at(intValue);
}

bool Plotter2DDlg::isSubValue(int value, int subValue) const
{
	if (value == subValue)
		return true;
	int i = 0;
	while (subValue) {
		if (!(value & (1 << i))) {
			if (subValue & 1)
				return false;
		}
		i++;
		subValue = subValue >> 1;
	}
	return true;
}

bool Plotter2DDlg::isPowerOf2(int value) const
{
	while (value) {
		if (value & 1) {
			return value == 1;
		}
		value = value >> 1;
	}
	return false;
}

void Plotter2DDlg::setObject(QObject *object)
{
	if (m_object == object)
		return;

	if (m_object) {
		saveExpandedState();
		QListIterator<QtProperty *> it(m_topLevelProperties);
		while (it.hasNext()) {
			m_browser->removeProperty(it.next());
		}
		m_topLevelProperties.clear();
	}

	m_object = object;

	if (!m_object)
		return;

	addClassProperties(m_object->metaObject());

	restoreExpandedState();
}

int Plotter2DDlg::flagToInt(const QMetaEnum &metaEnum, int flagValue) const
{
	if (!flagValue)
		return 0;
	int intValue = 0;
	QMap<int, int> valueMap; // dont show multiple enum values which have the same values
	int pos = 0;
	for (int i = 0; i < metaEnum.keyCount(); i++) {
		int value = metaEnum.value(i);
		if (!valueMap.contains(value) && isPowerOf2(value)) {
			if (isSubValue(flagValue, value))
				intValue |= (1 << pos);
			valueMap[value] = pos++;
		}
	}
	return intValue;
}

int Plotter2DDlg::intToFlag(const QMetaEnum &metaEnum, int intValue) const
{
	QMap<int, bool> valueMap; // dont show multiple enum values which have the same values
	QList<int> values;
	for (int i = 0; i < metaEnum.keyCount(); i++) {
		int value = metaEnum.value(i);
		if (!valueMap.contains(value) && isPowerOf2(value)) {
			valueMap[value] = true;
			values.append(value);
		}
	}
	int flagValue = 0;
	int temp = intValue;
	int i = 0;
	while (temp) {
		if (i >= values.count())
			return -1;
		if (temp & 1)
			flagValue |= values.at(i);
		i++;
		temp = temp >> 1;
	}
	return flagValue;
}


void Plotter2DDlg::addClassProperties(const QMetaObject *metaObject)
{
	if (!metaObject)
		return;

	addClassProperties(metaObject->superClass());

	QtProperty *classProperty = m_classToProperty.value(metaObject);
	if (!classProperty) {
		QString className = QLatin1String(metaObject->className());
		classProperty = m_manager->addProperty(QtVariantPropertyManager::groupTypeId(), className);
		m_classToProperty[metaObject] = classProperty;
		m_propertyToClass[classProperty] = metaObject;

		for (int idx = metaObject->propertyOffset(); idx < metaObject->propertyCount(); idx++) {
			QMetaProperty metaProperty = metaObject->property(idx);
			int type = metaProperty.userType();
			QtVariantProperty *subProperty = 0;
			if (!metaProperty.isReadable()) {
				subProperty = m_readOnlyManager->addProperty(QVariant::String, QLatin1String(metaProperty.name()));
				subProperty->setValue(QLatin1String("< Non Readable >"));
			} else if (metaProperty.isEnumType()) {
				if (metaProperty.isFlagType()) {
					subProperty = m_manager->addProperty(QtVariantPropertyManager::flagTypeId(), QLatin1String(metaProperty.name()));
					QMetaEnum metaEnum = metaProperty.enumerator();
					QMap<int, bool> valueMap;
					QStringList flagNames;
					for (int i = 0; i < metaEnum.keyCount(); i++) {
						int value = metaEnum.value(i);
						if (!valueMap.contains(value) && isPowerOf2(value)) {
							valueMap[value] = true;
							flagNames.append(QLatin1String(metaEnum.key(i)));
						}
					subProperty->setAttribute(QLatin1String("flagNames"), flagNames);
					subProperty->setValue(flagToInt(metaEnum, metaProperty.read(m_object).toInt()));
					}
				} else {
					subProperty = m_manager->addProperty(QtVariantPropertyManager::enumTypeId(), QLatin1String(metaProperty.name()));
					QMetaEnum metaEnum = metaProperty.enumerator();
					QMap<int, bool> valueMap; // dont show multiple enum values which have the same values
					QStringList enumNames;
					for (int i = 0; i < metaEnum.keyCount(); i++) {
						int value = metaEnum.value(i);
						if (!valueMap.contains(value)) {
							valueMap[value] = true;
							enumNames.append(QLatin1String(metaEnum.key(i)));
						}
					}
					subProperty->setAttribute(QLatin1String("enumNames"), enumNames);
					subProperty->setValue(enumToInt(metaEnum, metaProperty.read(m_object).toInt()));
				}
			} else if (m_manager->isPropertyTypeSupported(type)) {
				if (!metaProperty.isWritable())
					subProperty = m_readOnlyManager->addProperty(type, QLatin1String(metaProperty.name()) + QLatin1String(" (Non Writable)"));
				if (!metaProperty.isDesignable())
					subProperty = m_readOnlyManager->addProperty(type, QLatin1String(metaProperty.name()) + QLatin1String(" (Non Designable)"));
				else
					subProperty = m_manager->addProperty(type, QLatin1String(metaProperty.name()));
				subProperty->setValue(metaProperty.read(m_object));
			} else {

				addClassProperties(metaObject);
				subProperty = m_readOnlyManager->addProperty(QVariant::String, QLatin1String(metaProperty.name()));
//				subProperty->setValue(metaProperty.read(m_object));

				LOG(INFO) << "settting the value of class " << metaObject->className();
				LOG(INFO) << "settting the value of metapro " << metaProperty.name();

//				QVariant stuff = metaProperty.read(m_object);
//				if (stuff.canConvert<QBrush>())
//				{
//					LOG(INFO) << "can convert!";


//					QBrush  a = stuff.value<QBrush>();

//						LOG(INFO) << "found a good QCPAxis *";
//						const QMetaObject *mobj = a.metaObject();
//						if (mobj != NULL)
//						{
//							LOG(INFO) << "no null!";
//							addClassProperties(mobj);
//						}


//				}


//				LOG(INFO) << stuff.typeName();

//				if (g)
//					LOG(INFO) << "--> we have a valid scatterstyle!" ;



				subProperty->setValue(QLatin1String("< Unknown Type >"));
				subProperty->setEnabled(false);
			}
			classProperty->addSubProperty(subProperty);
			m_propertyToIndex[subProperty] = idx;
			m_classToIndexToProperty[metaObject][idx] = subProperty;
		}
	} else {
		updateClassProperties(metaObject, false);
	}

	m_topLevelProperties.append(classProperty);
	m_browser->addProperty(classProperty);
}

void Plotter2DDlg::updateClassProperties(const QMetaObject *metaObject, bool recursive)
{
	if (!metaObject)
		return;

	if (recursive)
		updateClassProperties(metaObject->superClass(), recursive);

	QtProperty *classProperty = m_classToProperty.value(metaObject);
	if (!classProperty)
		return;

	for (int idx = metaObject->propertyOffset(); idx < metaObject->propertyCount(); idx++) {
		QMetaProperty metaProperty = metaObject->property(idx);
		if (metaProperty.isReadable()) {
			if (m_classToIndexToProperty.contains(metaObject) && m_classToIndexToProperty[metaObject].contains(idx)) {
				QtVariantProperty *subProperty = m_classToIndexToProperty[metaObject][idx];
				if (metaProperty.isEnumType()) {
					if (metaProperty.isFlagType())
						subProperty->setValue(flagToInt(metaProperty.enumerator(), metaProperty.read(m_object).toInt()));
					else
						subProperty->setValue(enumToInt(metaProperty.enumerator(), metaProperty.read(m_object).toInt()));
				} else {
					subProperty->setValue(metaProperty.read(m_object));
				}
			}
		}
	}
}



void Plotter2DDlg::saveExpandedState()
{

}

void Plotter2DDlg::restoreExpandedState()
{

}





void Plotter2DDlg::slotValueChanged(QtProperty *property, const QVariant &value)
{

	LOG(INFO)  << "SLOT VALUE CHANGED";
	if (!m_propertyToIndex.contains(property))
		return;

	int idx = m_propertyToIndex.value(property);

	const QMetaObject *metaObject = m_object->metaObject();
	QMetaProperty metaProperty = metaObject->property(idx);
	if (metaProperty.isEnumType()) {
		if (metaProperty.isFlagType())
			metaProperty.write(m_object, intToFlag(metaProperty.enumerator(), value.toInt()));
		else
			metaProperty.write(m_object, intToEnum(metaProperty.enumerator(), value.toInt()));
	} else {
		metaProperty.write(m_object, value);
	}

	updateClassProperties(metaObject, true);
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
