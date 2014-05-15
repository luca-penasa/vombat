#ifndef COMPUTESMOOTHEDTIMESERIESXY_H
#define COMPUTESMOOTHEDTIMESERIESXY_H

//#include <BaseFilter.h>
#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <ccComputeSmoothedTimeSeriesXYDlg.h>

class ComputeSmoothedTimeSeriesXY: public BaseFilter
{
    Q_OBJECT
public:
    ComputeSmoothedTimeSeriesXY( ccPluginInterface * parent_plugin = 0);

    virtual int compute() ;

protected:
    virtual int checkSelected();

    virtual int openInputDialog();

    ccComputeSmoothedTimeSeriesXYDlg * m_dialog;
};

#endif // COMPUTESMOOTHEDTIMESERIESXY_H
