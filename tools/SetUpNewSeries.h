#ifndef ASSOCIATECLOUDTOMODEL_H
#define ASSOCIATECLOUDTOMODEL_H

#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <dialogs/ccTimeSeriesGeneratorEditorDlg.h>

#include <ccOutOfCore/ccTimeSeries.h>

class SetUpNewSeries : public BaseFilter
{
public:
    SetUpNewSeries(ccPluginInterface * parent_plugin);


protected:
    virtual int compute();

    virtual int checkSelected();

    virtual int openInputDialog();

    virtual int openOutputDialog();

    ComputeTimeSeriesDlg * m_dialog;

};

#endif // ASSOCIATECLOUDTOMODEL_H
