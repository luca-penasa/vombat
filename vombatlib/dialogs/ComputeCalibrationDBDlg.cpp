#include "ComputeCalibrationDBDlg.h"
#include "ui_ComputeCalibrationDBDlg.h"

#include <QSettings>

#include <QMessageBox>

ComputeCalibrationDBDlg::ComputeCalibrationDBDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComputeCalibrationDBDlg)
{
    ui->setupUi(this);

    connect(ui->btnLoadPCDFiles, SIGNAL(clicked()), this, SLOT(setPCDFiles()));
    connect(ui->btnSelectKeypointsFile, SIGNAL(clicked()), this, SLOT(setKeypointsFile()));
    connect(ui->btnSetNormalsPCDFile, SIGNAL(clicked()), this, SLOT(setNormalsFile()));

    // pcd files
    ui->listPCDFiles->clear();
    QSettings settings;
    settings.beginGroup("vombat/ComputeCalibrationDBDlg");
    QStringList PCDfiles = settings.value("PCDfiles",QStringList()).toStringList();

    ui->listPCDFiles->addItems(PCDfiles);

    // keypoint file
    ui->lneKeypointsPCDFile->clear();
    QString keypoints = settings.value("KeypointsFile",QString()).toString();
    ui->lneKeypointsPCDFile->setText(keypoints);

    // Normals file
    ui->lneNormalsPCDFile->clear();
    QString normals = settings.value("NormalsFile",QString()).toString();
    ui->lneNormalsPCDFile->setText(normals);

    settings.endGroup();

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


    QStringList new_list;
    new_list = QFileDialog::getOpenFileNames();

    if (!new_list.empty())
        ui->listPCDFiles->addItems(new_list);


    QSettings settings;
    settings.beginGroup("vombat/ComputeCalibrationDBDlg");
    settings.setValue("PCDfiles",new_list);
    settings.endGroup();

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

bool ComputeCalibrationDBDlg::checkInputValidity() const
{

    std::vector<std::string> pcd_files = getPCDFiles();
    if (pcd_files.empty())
        return false;


    for (int i = 0 ; i < pcd_files.size(); ++i)
    {
        QFile f (pcd_files.at(i).c_str());
        if (!f.exists())
            return false;
    }

    std::string keypoints = getKeypointsFile();
    if (!QFile(keypoints.c_str()).exists())
        return false;

    if (ui->groupUsePrecomputedNormals->isChecked())
    {
        std::string normals = getNormalsFile();
        if (!QFile(normals.c_str()).exists())
            return false;
    }
    return true;

}

void ComputeCalibrationDBDlg::setKeypointsFile()
{
    QString file_name = QFileDialog::getOpenFileName();

    if (file_name.size() != 0)
    {
        QSettings settings;
        settings.beginGroup("vombat/ComputeCalibrationDBDlg");
        settings.setValue("KeypointsFile",file_name);
        settings.endGroup();

        // now put the stuff in the line editor
        ui->lneKeypointsPCDFile->setText(file_name);
    }
}

void ComputeCalibrationDBDlg::setNormalsFile()
{
    QString file_name = QFileDialog::getOpenFileName();

    if (file_name.size() != 0)
    {
        QSettings settings;
        settings.beginGroup("vombat/ComputeCalibrationDBDlg");
        settings.setValue("NormalsFile",file_name);
        settings.endGroup();

        // now put the stuff in the line editor
        ui->lneNormalsPCDFile->setText(file_name);
    }

}
