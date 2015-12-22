#pragma once
#ifndef CLOUDTOPLANARSELECTION_H
#define CLOUDTOPLANARSELECTION_H

#include "BaseFilter.h"

class CloudToPlanarSelection : public BaseFilter {
    Q_OBJECT

public:
    CloudToPlanarSelection(ccPluginInterface* parent_plugin = 0);

protected:
    virtual int compute();

    virtual int openInputDialog();

    virtual int checkParameters();
};

#endif // DEFINE2DSELECTION_H
