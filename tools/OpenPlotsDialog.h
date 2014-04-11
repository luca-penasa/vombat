#ifndef PLOT_2D_H
#define PLOT_2D_H

#include <BaseFilter.h>
//#include <dialogs/ccCurvePlotterDlg.h>
#include <PlotterDlg.h>



class OpenPlotsDialog : public BaseFilter
{
public:
    OpenPlotsDialog(ccPluginInterface * parent_plugin = 0);

    virtual int compute();

    virtual int openInputDialog();

    virtual int checkSelected() {return 1;}

    PlotterDlg * getPlotterDlg()
    {
        return m_plotter_dialog;
    }

protected:
    PlotterDlg * m_plotter_dialog;
};

#endif // PLOT_2D_H
