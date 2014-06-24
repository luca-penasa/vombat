
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

Ui::ccCalibrateDeviceDlg *ccCalibrateDeviceDlg::getUI() const
{
    return ui;
}
