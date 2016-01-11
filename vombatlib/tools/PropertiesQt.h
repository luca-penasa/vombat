#pragma once
#ifndef PROPERTIES_QT_H
#define PROPERTIES_QT_H

#include "BaseFilter.h"

class PropertyBrowser;


class PropertiesQt : public BaseFilter {

    Q_OBJECT
public:
    PropertiesQt(ccPluginInterface* parent_plugin = 0);
    ~PropertiesQt();

    virtual int compute()
    {
        return 1;
    }

    int checkSelected()
    {
        return 1;
    }

    int openOutputDialog();


public slots:
    void selected(const ccHObject::Container  &objs);


private:
    PropertyBrowser* m_propertyBrowser;

    QDialog * m_dialog;
};

#endif // PROPERTIES_H
