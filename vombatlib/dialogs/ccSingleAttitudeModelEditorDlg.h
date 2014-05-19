#ifndef CCSINGLEATTITUDEMODELEDITORDLG_H
#define CCSINGLEATTITUDEMODELEDITORDLG_H

#include <QDialog>
#include <ccoutofcore/ccSingleAttitudeModel.h>


namespace Ui {
class ccSingleAttitudeModelEditorDlgUi;
}

class ccSingleAttitudeModelEditorDlg : public QDialog
{
    Q_OBJECT

public:
    //def const
    explicit ccSingleAttitudeModelEditorDlg(ccSingleAttitudeModel * model, QWidget *parent = 0);

    //destructor
    ~ccSingleAttitudeModelEditorDlg();


public slots:
    void stratShiftChanged(double val);

    void minSPChanged(double min_sp);

    void maxSPChanged(double max_sp);



private:
    Ui::ccSingleAttitudeModelEditorDlgUi *ui;

protected:

    void initFromModel();

    void linkToModel(ccSingleAttitudeModel * model);


    void updateConnections();

    ccSingleAttitudeModel * m_model;
};

#endif // CCSINGLEATTITUDEMODELEDITORDLG_H
