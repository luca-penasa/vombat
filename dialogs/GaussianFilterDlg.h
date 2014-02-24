#ifndef GAUSSIANFILTERDLG_H
#define GAUSSIANFILTERDLG_H

#include <QDialog>

namespace Ui {
class GaussianFilterDlg;
}

class GaussianFilterDlg : public QDialog
{
    Q_OBJECT

public:
    explicit GaussianFilterDlg(QWidget *parent = 0);
    ~GaussianFilterDlg();

    float getSigma() const;

    float getLeafSize() const;



private:
    Ui::GaussianFilterDlg *ui;
};

#endif // GAUSSIANFILTERDLG_H
