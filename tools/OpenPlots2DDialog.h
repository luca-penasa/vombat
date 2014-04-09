#ifndef VOMBAT_OPENPLOTS2D_H
#define VOMBAT_OPENPLOTS2D_H

#include <BaseFilter.h>
#include <PlotterDlg.h>


class OpenPlots2DDialog : public BaseFilter
{
public:
    OpenPlots2DDialog(ccPluginInterface * parent_plugin = 0);

    virtual int compute();

    virtual int openInputDialog();

    virtual int checkSelected() {return 1;}

    Plotter2DDlg * getPlotterDlg()
    {
        return m_plotter_dialog;
    }

protected:
    Plotter2DDlg * m_plotter_dialog;
};

#endif // PLOT_2D_H
