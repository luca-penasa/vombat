#pragma once
#ifndef VOMBAT_GAUSSIANFILTER_H
#define VOMBAT_GAUSSIANFILTER_H

#include "BaseFilter.h"

class GaussianFilterDlg;

class GaussianFilter : public BaseFilter {
public:
    GaussianFilter(ccPluginInterface* parent_plugin = 0);

    virtual int compute();

protected:
    virtual int checkSelected();

    int openInputDialog();

private:
    GaussianFilterDlg* m_dialog_;
};

#endif // VOMBAT_GAUSSIANFILTER_H
