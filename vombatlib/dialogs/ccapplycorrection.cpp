#include "ccapplycorrection.h"
#include "ui_ccapplycorrection.h"

ccApplyCorrection::ccApplyCorrection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ccApplyCorrection)
{
    ui->setupUi(this);
}

ccApplyCorrection::~ccApplyCorrection()
{
    delete ui;
}

QComboBox *ccApplyCorrection::getModelCombo()
{
	return ui->comboModel;
}

QComboBox *ccApplyCorrection::getFieldCombo()
{
	return ui->comboModel_2;
}
