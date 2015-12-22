#pragma once
#ifndef CREATE_STRATIGRAPHIC_CONSTRAIN_H
#define CREATE_STRATIGRAPHIC_CONSTRAIN_H

#include "BaseFilter.h"

class CreateStratigraphicConstrain : public BaseFilter {
public:
    CreateStratigraphicConstrain(ccPluginInterface* parent_plugin = 0);

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
