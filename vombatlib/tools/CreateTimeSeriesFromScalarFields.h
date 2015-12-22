#pragma once
#ifndef CREATE_TIME_SERIES_FROM_SCALAR_FIELDS_H
#define CREATE_TIME_SERIES_FROM_SCALAR_FIELDS_H

#include "BaseFilter.h"
class CreateTimeSeriesFromScalarFieldsDlg;

namespace spc {
spcFwdDeclSharedPtr(PointCloudBase)
}

class CreateTimeSeriesFromScalarFields : public BaseFilter {
public:
    CreateTimeSeriesFromScalarFields(ccPluginInterface* parent_plugin = 0);

    ~CreateTimeSeriesFromScalarFields();

public:
    int compute();

protected:
    int checkSelected();

    int openInputDialog();

protected:
    CreateTimeSeriesFromScalarFieldsDlg* m_dialog;

    spc::PointCloudBasePtr cloud_;
};

#endif // PLOT2DDATA_H
