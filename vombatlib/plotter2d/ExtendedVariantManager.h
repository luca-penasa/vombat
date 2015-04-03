#ifndef EXTENDEDVARIANTMANAGER_H
#define EXTENDEDVARIANTMANAGER_H
#include "qtvariantproperty.h"
#include "qteditorfactory.h"
//#include  <qtvariantproperty.h>

//#include "qttreepropertybrowser.h"

#include <qcustomplot.h>

#include "variantmanager.h"

//QCPRange range;

//class ExtendedVariantEditorFactory: public QtVariantEditorFactory
//{

//};

//Q_DECLARE_METATYPE(QCPRange)

class ExtenedVariantFactory: public QtVariantEditorFactory
{

};


class ExtendedVariantManager : public QtVariantPropertyManager
{
	Q_OBJECT
public:
	ExtendedVariantManager(QObject *parent = 0);

	~ExtendedVariantManager();

	bool isPropertyTypeSupported(int propertyType) const
	   {
		   if (propertyType == QVariant::PointF)
			   return true;

		   return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
	   }


	virtual QVariant value(const QtProperty *property) const;
	virtual int valueType(int propertyType) const;

	QString valueText(const QtProperty *property) const;

public slots:
	virtual void setValue(QtProperty *property, const QVariant &val);
protected:
	virtual void initializeProperty(QtProperty *property);
	virtual void uninitializeProperty(QtProperty *property);
private slots:
	void slotValueChanged(QtProperty *property, const QVariant &variantvalue);
	void slotPropertyDestroyed(QtProperty *property);
private:


	struct Data {
		QVariant value;
		QtVariantProperty *x;
		QtVariantProperty *y;
	};
	QMap<const QtProperty *, Data> propertyToData;
	QMap<const QtProperty *, QtProperty *> xToProperty;
	QMap<const QtProperty *, QtProperty *> yToProperty;








};

#endif // EXTENDEDVARIANTMANAGER_H
