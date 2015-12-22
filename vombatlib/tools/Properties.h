#pragma once
#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "BaseFilter.h"

class ccPropertiesTree;

class Properties : public BaseFilter {
public:
    Properties(ccPluginInterface* parent_plugin = 0);
    ~Properties();

    virtual int compute()
    {
        return 1;
    }

    int checkSelected()
    {
        return 1;
    }

    int openOutputDialog();

private:
    ccPropertiesTree* m_dialog;
};

#endif // PROPERTIES_H
