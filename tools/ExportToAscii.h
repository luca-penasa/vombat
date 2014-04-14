#ifndef EXPORTTOASCII_H
#define EXPORTTOASCII_H

//#include <BaseFilter.h>
#include <qPCL/PclUtils/filters/BaseFilter.h>
//#include <dialogs/ccCurvePlotterDlg.h>
#include <PlotterDlg.h>


class ExportToAscii : public BaseFilter
{
public:
    ExportToAscii(ccPluginInterface * parent_plugin = 0);

    virtual int compute();

    virtual int openInputDialog();

    virtual int checkSelected();



protected:

    QString m_filename;
};

#endif // PLOT_2D_H
