#include "ComputeStratigraphicPositionDlg.h"
#include "ui_ComputeStratigraphicPositionDlg.h"


#include <dialogs/FastCloudSelectionDlg.h>

//temp include
#include <iostream>
#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <ccHObjectCaster.h>
#include <ccPointCloud.h>
#include <ccConsole.h>


ComputeStratigraphicPositionDlg::ComputeStratigraphicPositionDlg(QWidget *parent) :
    ui(new Ui::ComputeStratigraphicPositionDlg)

{
    ui->setupUi(this);

}

ComputeStratigraphicPositionDlg::~ComputeStratigraphicPositionDlg()
{
    delete ui;
}

