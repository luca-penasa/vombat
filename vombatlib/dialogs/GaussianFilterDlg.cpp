#include "GaussianFilterDlg.h"
#include "ui_GaussianFilterDlg.h"

GaussianFilterDlg::GaussianFilterDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussianFilterDlg)
{
    ui->setupUi(this);
}

GaussianFilterDlg::~GaussianFilterDlg()
{
    delete ui;
}

float GaussianFilterDlg::getSigma() const
{
    return ui->spinSpatialSigma->value();
}

float GaussianFilterDlg::getLeafSize() const
{
    return ui->spinLeafSize->value();
}

