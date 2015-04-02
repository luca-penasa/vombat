#include "ExtendedVariantManager.h"

#include <QVariant>
#include "qtvariantproperty.h"
//#include "qteditorfactory.h"
//#include "qttreepropertybrowser.h"

#include <spc/core/logging.h>

ExtendedVariantManager::ExtendedVariantManager(QObject *parent): QtVariantPropertyManager(parent)
{

	connect(this, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
				this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));
	connect(this, SIGNAL(propertyDestroyed(QtProperty *)),
				this, SLOT(slotPropertyDestroyed(QtProperty *)));


}

ExtendedVariantManager::~ExtendedVariantManager()
{

}


void ExtendedVariantManager::slotValueChanged(QtProperty *property, const QVariant &variantvalue)
{
	if (xToProperty.contains(property)) {
		QtProperty *pointProperty = xToProperty[property];
		QVariant v = this->value(pointProperty);
		QCPRange p = v.value<QCPRange>();

		p.lower = variantvalue.value<double>();

		QVariant myvar(QCPRangeTypeId(), &p);
//		setValue(pointProperty, myvar);
	} else if (yToProperty.contains(property)) {
		QtProperty *pointProperty = yToProperty[property];
		QVariant v = this->value(pointProperty);
		QCPRange p = v.value<QCPRange>();
		p.upper  = variantvalue.value<double>();
		QVariant myvar(QCPRangeTypeId(), &p);
//		setValue(pointProperty, myvar);
	}
}

void ExtendedVariantManager::slotPropertyDestroyed(QtProperty *property)
{
	if (xToProperty.contains(property)) {
		QtProperty *pointProperty = xToProperty[property];
		propertyToData[pointProperty].x = 0;
		xToProperty.remove(property);
	} else if (yToProperty.contains(property)) {
		QtProperty *pointProperty = yToProperty[property];
		propertyToData[pointProperty].y = 0;
		yToProperty.remove(property);
	}
}



int ExtendedVariantManager::valueType(int propertyType) const
{
	if (propertyType == QCPRangeTypeId())
		return QCPRangeTypeId();

	return QtVariantPropertyManager::valueType(propertyType);
}

//! should return a QRange if property is of that type
QVariant ExtendedVariantManager::value(const QtProperty *property) const
{
	if (propertyToData.contains(property))
		return propertyToData[property].value;

	return QtVariantPropertyManager::value(property);
}

QString ExtendedVariantManager::valueText(const QtProperty *property) const
{

	if (propertyToData.contains(property)) {
		QVariant v = propertyToData[property].value;
		QCPRange p = v.value<QCPRange>();
		return QString(tr("(%1, %2)").arg(QString::number(p.lower))
								 .arg(QString::number(p.upper)));
	}
	return QtVariantPropertyManager::valueText(property);
}

void ExtendedVariantManager::setValue(QtProperty *property, const QVariant &val)
{
	if (propertyToData.contains(property)) {
		if (val.type() != QCPRangeTypeId() && !val.canConvert(QCPRangeTypeId()))
			return;
		QCPRange p = val.value<QCPRange>();
		Data d = propertyToData[property];

		QVariant myvar (QCPRangeTypeId(), &p);

		if (!myvar.isValid())
		{
			LOG(INFO) << "IVNALID!!";
						 return;
		}

//		QVariant myvar(QCPRangeTypeId());

		d.value = myvar;
		if (d.x)
			d.x->setValue(p.lower);
		if (d.y)
			d.y->setValue(p.upper);
		propertyToData[property] = d;
		emit valueChanged(property, myvar);
		emit propertyChanged(property);

		return;
	}
	QtVariantPropertyManager::setValue(property, val);
}

void ExtendedVariantManager::initializeProperty(QtProperty *property)
{

	if (propertyType(property) == QCPRangeTypeId()) {
		Data d;

		QCPRange voidrange (0, 0);
		QVariant myvar (QCPRangeTypeId(), &voidrange);
		d.value = myvar;

		ExtendedVariantManager *that = (ExtendedVariantManager *)this;

		d.x = that->addProperty(QVariant::Double);
		d.x->setPropertyName(tr("Position X"));
		property->addSubProperty(d.x);
		xToProperty[d.x] = property;

		d.y = that->addProperty(QVariant::Double);
		d.y->setPropertyName(tr("Position Y"));
		property->addSubProperty(d.y);
		yToProperty[d.y] = property;

		propertyToData[property] = d;
	}
	QtVariantPropertyManager::initializeProperty(property);
}

void ExtendedVariantManager::uninitializeProperty(QtProperty *property)
{
	if (propertyToData.contains(property)) {
		Data d = propertyToData[property];
		if (d.x)
			xToProperty.remove(d.x);
		if (d.y)
			yToProperty.remove(d.y);
		propertyToData.remove(property);
	}
	QtVariantPropertyManager::uninitializeProperty(property);
}

//int main(int argc, char **argv)
//{
//    QApplication app(argc, argv);

//    VariantManager *variantManager = new VariantManager();

//    QtVariantProperty *item = variantManager->addProperty(QVariant::PointF,
//                "PointF Property");
//    item->setValue(QPointF(2.5, 13.13));

//    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory();

//    QtTreePropertyBrowser ed1;
//    QtVariantPropertyManager *varMan = variantManager;
//    ed1.setFactoryForManager(varMan, variantFactory);
//    ed1.addProperty(item);


//    ed1.show();

//    int ret = app.exec();

//    delete variantFactory;
//    delete variantManager;

//    return ret;
//}
