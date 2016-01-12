#ifndef CropperDLG_H
#define CropperDLG_H

#include <QDialog>
#include <ccHObject.h>

namespace Ui {
class CropperDlg;
}

class QComboBox;

class CropperDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CropperDlg(QWidget *parent = 0);
    ~CropperDlg();

    void populateCombos();

    void clearCombos();

    ccHObject::Container getSelections();
//    ccHObject::Container getClouds();
    ccHObject::Container getCroppables();


    static ccHObject * comboToObject(const QComboBox * combo);

//    bool cropStrataTraces() const;

//    bool outputAttitudes() const;

//    bool outputRulers() const;


//        bool generateRegions() const;


private:
    Ui::CropperDlg *ui;

    // QWidget interface
//public slots:
//    virtual void setVisible(bool visible) override
//    {
//        if (visible == true)
//        {
//            clearCombos();
//            populateCombos();
//        }

//        QWidget::setVisible(visible);
//    }

};

#endif // CropperDLG_H
