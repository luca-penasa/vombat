
#include "ccComputeSmoothedTimeSeriesXYDlg.h"



ccComputeSmoothedTimeSeriesXYDlg::ccComputeSmoothedTimeSeriesXYDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ccComputeSmoothedTimeSeriesXYDlg)
{
    ui->setupUi(this);
}

ccComputeSmoothedTimeSeriesXYDlg::~ccComputeSmoothedTimeSeriesXYDlg()
{
    delete ui;
}

float ccComputeSmoothedTimeSeriesXYDlg::getBandwidth() const
{
    return this->ui->spinBandwidth->value();
}

float ccComputeSmoothedTimeSeriesXYDlg::getSamplingStep() const
{
    return this->ui->spinSamplingStep->value();
}

std::string ccComputeSmoothedTimeSeriesXYDlg::getXField() const
{
    return this->ui->comboX->getSelectedFiedName();
}

std::string ccComputeSmoothedTimeSeriesXYDlg::getYField() const
{
    return this->ui->comboY->getSelectedFiedName();
}

Ui::ccComputeSmoothedTimeSeriesXYDlg *ccComputeSmoothedTimeSeriesXYDlg::getUI() const
{
    return ui;
}
