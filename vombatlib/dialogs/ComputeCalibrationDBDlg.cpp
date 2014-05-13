#include "ComputeCalibrationDBDlg.h"
#include "ui_ComputeCalibrationDBDlg.h"

#include <QMessageBox>

ComputeCalibrationDBDlg::ComputeCalibrationDBDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComputeCalibrationDBDlg)
{
    ui->setupUi(this);

    connect(ui->btnLoadPCDFiles, SIGNAL(clicked()), this, SLOT(setPCDFiles()));
    connect(ui->btnSelectKeypointsFile, SIGNAL(clicked()), this, SLOT(setKeypointsFile()));
    connect(ui->btnSetNormalsPCDFile, SIGNAL(clicked()), this, SLOT(setNormalsFile()));
}

ComputeCalibrationDBDlg::~ComputeCalibrationDBDlg()
{
    delete ui;
}

std::vector<std::string> ComputeCalibrationDBDlg::getPCDFiles() const
{
    std::vector<std::string> out;

    for (int i = 0; i < ui->listPCDFiles->count(); ++i)
        out.push_back(ui->listPCDFiles->item(i)->text().toStdString());

    return out;
}

std::string ComputeCalibrationDBDlg::getNormalsFile() const
{
    return ui->lneNormalsPCDFile->text().toStdString();
}

std::string ComputeCalibrationDBDlg::getKeypointsFile() const
{
    return ui->lneKeypointsPCDFile->text().toStdString();
}

void ComputeCalibrationDBDlg::setPCDFiles()
{
    QStringList file_names = QFileDialog::getOpenFileNames();
    ui->listPCDFiles->addItems(file_names);

}

double ComputeCalibrationDBDlg::getKernelSize() const
{
    return ui->spinIntensityKernelSize->value();
}

double ComputeCalibrationDBDlg::getMaxDistanceForNormals() const
{
    return ui->spinMaxDistanceForNormal->value();
}

bool ComputeCalibrationDBDlg::usePrecomputedNormals() const
{
    return ui->groupUsePrecomputedNormals->isChecked();
}

void ComputeCalibrationDBDlg::setKeypointsFile()
{
    QString file_name = QFileDialog::getOpenFileName();

    // now put the stuff in the file list
    ui->lneKeypointsPCDFile->setText(file_name);
}

void ComputeCalibrationDBDlg::setNormalsFile()
{
    QString file_name = QFileDialog::getOpenFileName();

    // now put the stuff in the file list
    ui->lneNormalsPCDFile->setText(file_name);
}
