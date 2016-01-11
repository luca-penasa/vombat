#pragma once
#ifndef FITGEOLOGICALORIENTATION_H
#define FITGEOLOGICALORIENTATION_H

//#include <BaseFilter.h>
#include "BaseFilter.h"

class ccAttitude;

class FitAttitude : public BaseFilter {
public:
    FitAttitude(ccPluginInterface* parent_plugin = 0);

    virtual int compute();


    static ccAttitude * fitAttitude(const ccHObject::Container &fittable);

protected:
    virtual int checkSelected();
};

#endif // FITGEOLOGICALORIENTATION_H
