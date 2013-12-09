#include "ccTimeSeriesGenerator.h"
#include <dialogs/ccTimeSeriesGeneratorEditorDlg.h>


ccTimeSeriesGenerator::ccTimeSeriesGenerator()
{

    QVariant var(QString("Permits to compute time series from cloud, scalar field and model"));
    setMetaData(QString("[vombat][TimeSeriesGenerator]"), var);
}

void ccTimeSeriesGenerator::initEditDlg()
{        
    m_edit_dlg = new ComputeTimeSeriesDlg();
}

void ccTimeSeriesGenerator::updateEditDlg()
{
    ComputeTimeSeriesDlg * asitis = static_cast<ComputeTimeSeriesDlg *> (m_edit_dlg);
    asitis->initWithTree();
}
