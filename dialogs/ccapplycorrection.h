#ifndef CCAPPLYCORRECTION_H
#define CCAPPLYCORRECTION_H

#include <QDialog>
#include <QComboBox>
namespace Ui {
class ccApplyCorrection;
}

class ccApplyCorrection : public QDialog
{
    Q_OBJECT

public:
    explicit ccApplyCorrection(QWidget *parent = 0);
    ~ccApplyCorrection();

    QComboBox * getModelCombo();


private:
    Ui::ccApplyCorrection *ui;
};

#endif // CCAPPLYCORRECTION_H
