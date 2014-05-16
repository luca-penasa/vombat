#ifndef CREATE_TIME_SERIES_FROM_SCALAR_FIELDS_DLG_H
#define CREATE_TIME_SERIES_FROM_SCALAR_FIELDS_DLG_H

#include <QDialog>

namespace Ui {
class CreateTimeSeriesFromScalarFieldsDlg;
}

class CreateTimeSeriesFromScalarFieldsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTimeSeriesFromScalarFieldsDlg(QWidget *parent = 0);
    ~CreateTimeSeriesFromScalarFieldsDlg();

    //lets try with to get access to the ui this way
    Ui::CreateTimeSeriesFromScalarFieldsDlg * getUi () const;



private:
    Ui::CreateTimeSeriesFromScalarFieldsDlg *ui;
};

#endif
