#ifndef CCCALIBRATEDEVICEDLG_H
#define CCCALIBRATEDEVICEDLG_H

#include <QDialog>
#include "ui_ccCalibrateDeviceDlg.h"



class ccCalibrateDeviceDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ccCalibrateDeviceDlg(QWidget *parent = 0);
    ~ccCalibrateDeviceDlg();

//    float getBandwidth() const;

//    float getSamplingStep() const;

//    std::string getDistanceField () const;
//    std::string getIntensityField () const;


    Ui::ccCalibrateDeviceDlg * getUI() const;


private:
    Ui::ccCalibrateDeviceDlg *ui;
};

#endif // CCCALIBRATEDEVICEDLG_H
