#pragma once
#ifndef FlipModel_H
#define FlipModel_H

#include "BaseFilter.h"

class FlipModel : public BaseFilter {
public:
    FlipModel(ccPluginInterface* parent_plugin = 0);

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

#endif // FlipModel_H
