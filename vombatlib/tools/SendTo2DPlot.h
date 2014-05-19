#ifndef SENDTO2DPLOT_H
#define SENDTO2DPLOT_H
#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <dialogs/SendTo2DPlotDlg.h>



class SendTo2DPlot: public BaseFilter
{
public:
    SendTo2DPlot(ccPluginInterface * parent_plugin = 0);

    virtual int compute();

protected:
    virtual int checkSelected();

    SendTo2DPlotDlg * m_dialog;



    // BaseFilter interface
protected:
    int openInputDialog()
    {
        if (!m_dialog)
        {
            m_dialog = new SendTo2DPlotDlg();
        }

        return m_dialog->exec() ? 1 : 0;

    }
};

#endif // SENDTO2DPLOT_H
