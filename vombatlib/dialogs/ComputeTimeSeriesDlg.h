#ifndef COMPUTETIMESERIESDLG_H
#define COMPUTETIMESERIESDLG_H

#include "ui_ComputeTimeSeriesDlg.h"

class ComputeTimeSeriesDlg : public QDialog, private Ui::ComputeTimeSeriesDlg
{
    Q_OBJECT

public:
    explicit ComputeTimeSeriesDlg(QWidget *parent = 0);

public slots:
    void changedCloudSelection(int n);
};

#endif // COMPUTETIMESERIESDLG_H
