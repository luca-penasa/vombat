

#include "ccSingleAttitudeModelEditorDlg.h"
#include <ui_ccSingleAttitudeModelEditorDlg.h>
#include <ccoutofcore/ccSingleAttitudeModel.h>



ccSingleAttitudeModelEditorDlg::ccSingleAttitudeModelEditorDlg(ccSingleAttitudeModel * model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ccSingleAttitudeModelEditorDlgUi)
{   
    ui->setupUi(this);

    linkToModel(model);
}

ccSingleAttitudeModelEditorDlg::~ccSingleAttitudeModelEditorDlg()
{
    delete ui;
}

void ccSingleAttitudeModelEditorDlg::stratShiftChanged(double val)
{
    m_model->getModel()->setStratigraphicShift((float)val);
    m_model->updateInternals();
    m_model->redrawDisplay();
}


void ccSingleAttitudeModelEditorDlg::minSPChanged(double min_sp)
{
    m_model->setMinSp(min_sp);
    m_model->updateInternals();
    m_model->redrawDisplay();
    ui->spinMaxSP->setMinimum(min_sp);

}

void ccSingleAttitudeModelEditorDlg::maxSPChanged(double max_sp)
{
    m_model->setMaxSp(max_sp);
    m_model->updateInternals();
    m_model->redrawDisplay();
    ui->spinMinSP->setMaximum(max_sp);
}

void ccSingleAttitudeModelEditorDlg::initFromModel()
{
    ui->spinStratShift->setValue((double) m_model->getModel()->getStratigraphicShift());
    ui->spinMaxSP->setValue((double) m_model->getMaxSp());
    ui->spinMinSP->setValue((double) m_model->getMinSp());
}

void ccSingleAttitudeModelEditorDlg::linkToModel(ccSingleAttitudeModel *model)
{
    m_model = model;
    initFromModel();
    updateConnections();
}

void ccSingleAttitudeModelEditorDlg::updateConnections()
{
    connect (this->ui->spinStratShift, SIGNAL(valueChanged(double)), this, SLOT(stratShiftChanged(double)));
    connect (this->ui->spinMinSP, SIGNAL(valueChanged(double)), this, SLOT(minSPChanged(double)));
    connect (this->ui->spinMaxSP, SIGNAL(valueChanged(double)), this, SLOT(maxSPChanged(double)));

}
