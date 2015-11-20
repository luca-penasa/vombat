#pragma once

#ifndef NEW_ROI_H
#define NEW_ROI_H

#include "BaseFilter.h"

class NewRoi: public BaseFilter
{
Q_OBJECT

public:
    NewRoi(ccPluginInterface * parent_plugin = 0);

protected:
   virtual int compute();

    virtual int openInputDialog();

    virtual int checkParameters();

    // BaseFilter interface
protected:
    int checkSelected();
};

#endif // DEFINE2DSELECTION_H
