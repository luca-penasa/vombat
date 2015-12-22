#pragma once
#ifndef LINK_MODEL_TO_RUBBERBAND_H
#define LINK_MODEL_TO_RUBBERBAND_H

#include "BaseFilter.h"

class LinkModelToRubberband : public BaseFilter {
public:
    LinkModelToRubberband(ccPluginInterface* parent_plugin = 0);

    ~LinkModelToRubberband()
    {
    }

    virtual int compute();

protected:
    virtual int checkSelected();
};

#endif // ATTITUDE_TO_MDOEL_H
