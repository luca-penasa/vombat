#ifndef ANALYZERDLG_H
#define ANALYZERDLG_H

#include <QDialog>
#include <ccHObject.h>

#include "ui_AnalyzerDlg.h"

class QComboBox;

class AnalyzerDlg : public QDialog, public Ui::AnalyzerDlg
{
    Q_OBJECT

public:
    explicit AnalyzerDlg(QWidget *parent = 0);
    ~AnalyzerDlg();

//    void populateCombos();

//    void clearCombos();

//    ccHObject::Container getRegions();
////    ccHObject::Container getClouds();
//    ccHObject::Container getTraces();


//    static ccHObject * comboToObject(const QComboBox * combo);

//    bool cropStrataTraces() const;

//    bool outputAttitudes() const;

//    bool outputRulers() const;






};

#endif // ANALYZERDLG_H
