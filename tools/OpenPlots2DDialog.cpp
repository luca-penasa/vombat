#include "OpenPlots2DDialog.h"
#include <vombat.h>
#include <Plotter2DDlg.h>

OpenPlots2DDialog::OpenPlots2DDialog(ccPluginInterface *parent_plugin) : BaseFilter(FilterDescription(   "Show 2d Plots ",
                                                     "Open the 2D plots dialog",
                                                     "Open the 2D plots dialog",
                                                                                                     ":/toolbar/icons/2dplot.png" ), parent_plugin), m_plotter_dialog(0)
{
    this->setShowProgressBar(false);
    m_plotter_dialog = new Plotter2DDlg();
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
        m_plotter_dialog->show();

    else
        m_plotter_dialog->setVisible(false);

    return 1;
}
