#ifndef PROPERTYINSPECTOR_H
#define PROPERTYINSPECTOR_H

#include <QWidget>
#include <qtpropertybrowser.h>
#include <qttreepropertybrowser.h>
class PropertyBrowser: public QtTreePropertyBrowser
{
    Q_OBJECT
public:
    PropertyBrowser(QWidget *parent) : QtTreePropertyBrowser(parent)
    {

    }

};

#endif // PROPERTYINSPECTOR_H
