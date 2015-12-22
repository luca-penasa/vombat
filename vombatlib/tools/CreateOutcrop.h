#pragma once
#ifndef CREATE_OUTCROP_H
#define CREATE_OUTCROP_H

#include "BaseFilter.h"

class CreateOutcrop : public BaseFilter {
public:
    CreateOutcrop(ccPluginInterface* parent_plugin = 0);

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

#endif // CreateOutcrop_H
