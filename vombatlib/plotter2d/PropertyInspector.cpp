#include "PropertyInspector.h"

//#include <QtDoublePropertyManager>
#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "qttreepropertybrowser.h"

PropertyInspector::PropertyInspector(QWidget *parent) : QtTreePropertyBrowsert(parent)
{
    doubleManager = new QtDoublePropertyManager(this);
    stringManager = new QtStringPropertyManager(this);
    colorManager = new QtColorPropertyManager(this);
    fontManager = new QtFontPropertyManager(this);
    pointManager = new QtPointPropertyManager(this);
    sizeManager = new QtSizePropertyManager(this);
}
