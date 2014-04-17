#ifndef CC_COMPUTE_SMOOTHED_TIME_SERIES_XY_DLG_H
#define CC_COMPUTE_SMOOTHED_TIME_SERIES_XY_DLG_H

#include <QDialog>
#include "ui_ccComputeSmoothedTimeSeriesXYDlg.h"



class ccComputeSmoothedTimeSeriesXYDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ccComputeSmoothedTimeSeriesXYDlg(QWidget *parent = 0);
    ~ccComputeSmoothedTimeSeriesXYDlg();

    float getBandwidth() const;

    float getSamplingStep() const;

    std::string getXField () const;
    std::string getYField () const;


    Ui::ccComputeSmoothedTimeSeriesXYDlg * getUI() const;


private:
    Ui::ccComputeSmoothedTimeSeriesXYDlg *ui;
};

#endif // CC_COMPUTE_SMOOTHED_TIME_SERIES_XY_DLG_H
