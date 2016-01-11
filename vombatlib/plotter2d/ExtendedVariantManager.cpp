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


void ExtendedVariantManager::slotValueChanged(QtProperty *property, const QVariant &value)
{
	if (xToProperty.contains(property)) {
		QtProperty *pointProperty = xToProperty[property];
		QVariant v = this->value(pointProperty);
		QPointF p = v.value<QPointF>();
		p.setX(value.value<double>());
		setValue(pointProperty, p);
	} else if (yToProperty.contains(property)) {
		QtProperty *pointProperty = yToProperty[property];
		QVariant v = this->value(pointProperty);
		QPointF p = v.value<QPointF>();
		p.setY(value.value<double>());
		setValue(pointProperty, p);
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
	if (propertyType == QVariant::PointF)
		return QVariant::PointF;

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
		QPointF p = v.value<QPointF>();
		return QString(tr("(%1, %2)").arg(QString::number(p.x()))
								 .arg(QString::number(p.y())));
	}
	return QtVariantPropertyManager::valueText(property);
}

void ExtendedVariantManager::setValue(QtProperty *property, const QVariant &val)
{
	if (propertyToData.contains(property)) {
		if (val.type() != QVariant::PointF && !val.canConvert(QVariant::PointF))
			return;
		QPointF p = val.value<QPointF>();
		Data d = propertyToData[property];
		d.value = p;
		if (d.x)
			d.x->setValue(p.x());
		if (d.y)
			d.y->setValue(p.y());
		propertyToData[property] = d;
		emit propertyChanged(property);
		emit valueChanged(property, p);
		return;
	}
	QtVariantPropertyManager::setValue(property, val);
}

void ExtendedVariantManager::initializeProperty(QtProperty *property)
{
	if (propertyType(property) == QVariant::PointF) {
		Data d;

		d.value = QPointF(0, 0);

		VariantManager *that = (VariantManager *)this;

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

