#pragma once
#ifndef FITGEOLOGICALORIENTATION_H
#define FITGEOLOGICALORIENTATION_H

//#include <BaseFilter.h>
#include "BaseFilter.h"

class ccAttitude;
class ccFitAttitudeDlg;

class FitAttitude : public BaseFilter {
public:
    FitAttitude(ccPluginInterface* parent_plugin = 0);

    virtual int compute() override;


    static ccAttitude * fitAttitude(const ccHObject::Container &fittable);

protected:
    virtual int checkSelected() override;

    virtual int openInputDialog() override;


   ccFitAttitudeDlg * m_dlg = nullptr;

};



#endif // FITGEOLOGICALORIENTATION_H
