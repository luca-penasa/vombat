/****************************************************************************
**
** Copyright (C) 2006 Trolltech ASA. All rights reserved.
**
** This file is part of the documentation of Qt. It was originally
** published as part of Qt Quarterly.
**
** This file may be used under the terms of the GNU General Public License
** version 2.0 as published by the Free Software Foundation or under the
** terms of the Qt Commercial License Agreement. The respective license
** texts for these are provided with the open source and commercial
** editions of Qt.
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "variantmanager.h"

#include <spc/core/logging.h>





int VariantManager::filePathTypeId()
{
	return qMetaTypeId<FilePathPropertyType>();
}

int VariantManager::QCPRangeTypeId()
{
	return qMetaTypeId<QCPRange>();

}

bool VariantManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == filePathTypeId())
        return true;

	if (propertyType == QCPRangeTypeId())
		return true;

    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}

int VariantManager::valueType(int propertyType) const
{
    if (propertyType == filePathTypeId())
        return QVariant::String;

	if (propertyType == QCPRangeTypeId())
		return QCPRangeTypeId();

    return QtVariantPropertyManager::valueType(propertyType);
}

QVariant VariantManager::value(const QtProperty *property) const
{

    if (theValues.contains(property))
        return theValues[property].value;

	if (qcpRangeValues.contains(property))
	{
		QCPRange data = qcpRangeValues[property].value;
		return QVariant::fromValue(data);
	}


    return QtVariantPropertyManager::value(property);
}

QStringList VariantManager::attributes(int propertyType) const
{
    if (propertyType == filePathTypeId()) {
        QStringList attr;
        attr << QLatin1String("filter");
        return attr;
    }
    return QtVariantPropertyManager::attributes(propertyType);
}

int VariantManager::attributeType(int propertyType, const QString &attribute) const
{
    if (propertyType == filePathTypeId()) {
        if (attribute == QLatin1String("filter"))
            return QVariant::String;
        return 0;
    }
    return QtVariantPropertyManager::attributeType(propertyType, attribute);
}

QVariant VariantManager::attributeValue(const QtProperty *property, const QString &attribute)
{
    if (theValues.contains(property)) {
        if (attribute == QLatin1String("filter"))
            return theValues[property].filter;
        return QVariant();
    }
    return QtVariantPropertyManager::attributeValue(property, attribute);
}

QString VariantManager::valueText(const QtProperty *property) const
{
    if (theValues.contains(property))
        return theValues[property].value;

	if (qcpRangeValues.contains(property))
	{
		QCPRange p = qcpRangeValues[property].value;
		return QString(tr("(%1, %2)").arg(QString::number(p.lower))
								 .arg(QString::number(p.upper)));
	}


    return QtVariantPropertyManager::valueText(property);
}

// the porpuse of this is getting the data from val and change the content of the
// qcpRangeValues with that value
void VariantManager::setValue(QtProperty *property, const QVariant &val)
{
	LOG(INFO) << "calling setValue from the variantManager";
    if (theValues.contains(property)) {
		if (val.type() != QVariant::String && !val.canConvert(QVariant::String))
            return;
		// get out the value from val
		QString str = val.value<QString>();

		// retrieve the stored data container
        Data d = theValues[property];
        if (d.value == str)
            return;

		// substitute the value with the new one from val
        d.value = str;

		// set back into the map
        theValues[property] = d;

		// emit stuff
        emit propertyChanged(property);
        emit valueChanged(property, str);
        return;
    }

	if (qcpRangeValues.contains(property))
	{
		if (val.type() != QCPRangeTypeId() && !val.canConvert<QCPRange>())
			return;

		QCPRange newrange =val.value<QCPRange>();
		QCPRangeData data = qcpRangeValues[property];
		data.value = newrange;
		qcpRangeValues[property] = data;
		emit propertyChanged(property);

		QVariant variant(QCPRangeTypeId(), &newrange);

//		emit valueChanged(property, variant);
		return;

	}
    QtVariantPropertyManager::setValue(property, val);
}

void VariantManager::setAttribute(QtProperty *property,
                const QString &attribute, const QVariant &val)
{
    if (theValues.contains(property)) {
        if (attribute == QLatin1String("filter")) {
            if (val.type() != QVariant::String && !val.canConvert(QVariant::String))
                return;
			QString str = val.value<QString>();
            Data d = theValues[property];
            if (d.filter == str)
                return;
            d.filter = str;
            theValues[property] = d;
            emit attributeChanged(property, attribute, str);
        }
        return;
    }
    QtVariantPropertyManager::setAttribute(property, attribute, val);
}

void VariantManager::initializeProperty(QtProperty *property)
{
    if (propertyType(property) == filePathTypeId())
        theValues[property] = Data();

	if (propertyType(property) == QCPRangeTypeId())
	{
		qcpRangeValues[property] = QCPRangeData();
	}

    QtVariantPropertyManager::initializeProperty(property);
}

void VariantManager::uninitializeProperty(QtProperty *property)
{
    theValues.remove(property);
	qcpRangeValues.remove(property);

    QtVariantPropertyManager::uninitializeProperty(property);
}

