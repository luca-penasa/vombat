#pragma once
#ifndef ADDSAMPLE_H
#define ADDSAMPLE_H

#include "BaseFilter.h"

class AddSample : public BaseFilter {
public:
    AddSample(ccPluginInterface* parent_plugin = 0);

    // BaseFilter interface
public:
    int compute();

protected:
    int checkSelected();

    int openInputDialog()
    {
        return 1;
    }
};

#endif // ADDSAMPLE_H
