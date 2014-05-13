#ifndef COMPUTECALIBRATIONDBDLG_H
#define COMPUTECALIBRATIONDBDLG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class ComputeCalibrationDBDlg;
}

class ComputeCalibrationDBDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ComputeCalibrationDBDlg(QWidget *parent = 0);
    ~ComputeCalibrationDBDlg();

    std::vector<std::string> getPCDFiles() const;

    std::string getNormalsFile() const;

    std::string getKeypointsFile() const;

    double getKernelSize() const;

    double getMaxDistanceForNormals() const;

    bool usePrecomputedNormals() const;
public slots:
    void setPCDFiles();

    void setKeypointsFile();

    void setNormalsFile();
private:
    Ui::ComputeCalibrationDBDlg *ui;


};

#endif // COMPUTECALIBRATIONDBDLG_H
