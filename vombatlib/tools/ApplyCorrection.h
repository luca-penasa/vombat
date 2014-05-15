#ifndef APPLYCORRECTION_H
#define APPLYCORRECTION_H


#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <visualization/PlotterDlg.h>


class ApplyCorrection : public BaseFilter
{
public:
    ApplyCorrection(ccPluginInterface * parent_plugin = 0);

    virtual int compute();

    virtual int openInputDialog();

    virtual int checkSelected();



protected:

    QString m_filename;

    ccHObject * model_;
};

#endif // PLOT_2D_H
