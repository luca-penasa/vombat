#include "OpenPlots2DDialog.h"
#include <vombat.h>
#include <Plotter2DDlg.h>

OpenPlots2DDialog::OpenPlots2DDialog(ccPluginInterface *parent_plugin) : BaseFilter(FilterDescription(   "Show 2d Plots ",
                                                     "Open the 2D plots dialog",
                                                     "Open the 2D plots dialog",
                                                                                                     ":/toolbar/icons/plotter.png" ), parent_plugin), m_plotter_dialog(0)
{
    this->setShowProgressBar(false);
    m_plotter_dialog = new Plotter2DDlg(0);
    m_plotter_dialog->setVisible(false);
}

int
OpenPlots2DDialog::compute()
{
    return 1;
}

int OpenPlots2DDialog::openInputDialog()
{
    if (!m_plotter_dialog->isVisible())
        m_plotter_dialog->setVisible(true);
    else
        m_plotter_dialog->setVisible(false);

    return 1;
}

Plotter2DDlg *OpenPlots2DDialog::getPlotterDlg()
{
    return m_plotter_dialog;
}



OpenPlots2DDialog::~OpenPlots2DDialog()
{
    delete m_plotter_dialog;
}
