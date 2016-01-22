#pragma once
#ifndef ADDSAMPLE_H
#define ADDSAMPLE_H

#include "BaseFilter.h"

class TestVTK : public BaseFilter {
public:
    TestVTK(ccPluginInterface* parent_plugin = 0);

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
