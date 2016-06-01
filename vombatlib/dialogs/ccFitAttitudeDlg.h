#ifndef CCFITATTITUDEDLG_H
#define CCFITATTITUDEDLG_H

#include "ui_ccFitAttitudeDlg.h"

class ccFitAttitudeDlg : public QDialog, private Ui::ccFitAttitudeDlg
{
    Q_OBJECT

public:
    explicit ccFitAttitudeDlg(QWidget *parent = 0);


    bool isUniqueNormal() const
    {
        return this->checkBoxUniqueNormal->isChecked();
    }
};

#endif // CCFITATTITUDEDLG_H
