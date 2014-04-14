
#include "ccCalibrateDeviceDlg.h"



ccCalibrateDeviceDlg::ccCalibrateDeviceDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ccCalibrateDeviceDlg)
{
    ui->setupUi(this);
}

ccCalibrateDeviceDlg::~ccCalibrateDeviceDlg()
{
    delete ui;
}

float ccCalibrateDeviceDlg::getBandwidth() const
{
    return this->ui->spinBandwidth->value();
}

float ccCalibrateDeviceDlg::getSamplingStep() const
{
    return this->ui->spinSamplingStep->value();
}

std::string ccCalibrateDeviceDlg::getDistanceField() const
{
    return this->ui->comboDistance->getSelectedFiedName();
}

std::string ccCalibrateDeviceDlg::getIntensityField() const
{
    return this->ui->comboIntensity->getSelectedFiedName();
}

Ui::ccCalibrateDeviceDlg *ccCalibrateDeviceDlg::getUI() const
{
    return ui;
}
