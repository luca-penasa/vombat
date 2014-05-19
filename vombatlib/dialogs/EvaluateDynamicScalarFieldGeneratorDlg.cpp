#include "dialogs/EvaluateDynamicScalarFieldGeneratorDlg.h"
#include "ui_EvaluateDynamicScalarFieldGeneratorDlg.h"

#include <dialogs/ccHObjectSelectionDlgSimple.h>
//temp include

#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <ccHObjectCaster.h>
#include <ccPointCloud.h>



EvaluateDynamicScalarFieldGeneratorDlg::EvaluateDynamicScalarFieldGeneratorDlg(QWidget *parent) :
    ui(new Ui::EvaluateDynamicScalarFieldGeneratorDlg)

{
    ui->setupUi(this);

}

EvaluateDynamicScalarFieldGeneratorDlg::~EvaluateDynamicScalarFieldGeneratorDlg()
{
    delete ui;
}

