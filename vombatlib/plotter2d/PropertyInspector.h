#ifndef PROPERTYINSPECTOR_H
#define PROPERTYINSPECTOR_H

#include <QWidget>
#include <qtpropertybrowser.h>
#include <qttreepropertybrowser.h>
class PropertyInspector: public QtTreePropertyBrowser
{
    Q_OBJECT
public:
    PropertyInspector(QWidget *parent);

private slots:
    void valueChanged(QtProperty *property, double value);
    void valueChanged(QtProperty *property, const QString &value);
    void valueChanged(QtProperty *property, const QColor &value);
    void valueChanged(QtProperty *property, const QFont &value);
    void valueChanged(QtProperty *property, const QPoint &value);
    void valueChanged(QtProperty *property, const QSize &value);

private:

    class QtDoublePropertyManager *doubleManager;
    class QtStringPropertyManager *stringManager;
    class QtColorPropertyManager *colorManager;
    class QtFontPropertyManager *fontManager;
    class QtPointPropertyManager *pointManager;
    class QtSizePropertyManager *sizeManager;
};

#endif // PROPERTYINSPECTOR_H
