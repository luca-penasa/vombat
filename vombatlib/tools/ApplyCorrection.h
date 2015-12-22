#pragma once
#ifndef APPLYCORRECTION_H
#define APPLYCORRECTION_H

#include "BaseFilter.h"

class ccScalarField;
class ccPointCloud;
class ccHObject;
class ccTimeSeries;

class ApplyCorrection : public BaseFilter {
public:
    ApplyCorrection(ccPluginInterface* parent_plugin = 0);

    virtual int compute();

    virtual int openInputDialog();

    virtual int checkSelected();

protected:
    QString m_filename;

    ccTimeSeries* ts_;

    ccScalarField* field_;

    ccPointCloud* cloud_;
};

#endif // PLOT_2D_H
