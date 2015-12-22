#include "CreateTimeSeriesFromScalarFieldsDlg.h"
#include "ui_CreateTimeSeriesFromScalarFieldsDlg.h"

CreateTimeSeriesFromScalarFieldsDlg::CreateTimeSeriesFromScalarFieldsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTimeSeriesFromScalarFieldsDlg)
{
    ui->setupUi(this);
}

CreateTimeSeriesFromScalarFieldsDlg::~CreateTimeSeriesFromScalarFieldsDlg()
{
    delete ui;
}

Ui::CreateTimeSeriesFromScalarFieldsDlg *CreateTimeSeriesFromScalarFieldsDlg::getUi() const
{
    return ui;
}
