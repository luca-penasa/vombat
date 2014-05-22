#ifndef SENDTO2DPLOT_H
#define SENDTO2DPLOT_H
#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <dialogs/SendTo2DPlotDlg.h>

class ccTimeSeries;

class SendTo2DPlot: public BaseFilter
{
    Q_OBJECT // so we can have signals
public:
    SendTo2DPlot(ccPluginInterface * parent_plugin = 0);

    virtual int compute();


signals:
    void handleNewPlot(ccTimeSeries *serie);

protected:
    virtual int checkSelected();

    SendTo2DPlotDlg * m_dialog;

    void connectToPlotter();



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
