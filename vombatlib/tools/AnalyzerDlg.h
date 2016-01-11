#ifndef ANALYZERDLG_H
#define ANALYZERDLG_H

#include <QDialog>
#include <ccHObject.h>

namespace Ui {
class AnalyzerDlg;
}

class QComboBox;

class AnalyzerDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AnalyzerDlg(QWidget *parent = 0);
    ~AnalyzerDlg();

    void populateCombos();

    void clearCombos();

    ccHObject::Container getRegions();
//    ccHObject::Container getClouds();
    ccHObject::Container getTraces();


    static ccHObject * comboToObject(const QComboBox * combo);

    bool cropStrataTraces() const;

    bool outputAttitudes() const;

    bool outputRulers() const;


//        bool generateRegions() const;


private:
    Ui::AnalyzerDlg *ui;

    // QWidget interface
public slots:
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

#endif // ANALYZERDLG_H
