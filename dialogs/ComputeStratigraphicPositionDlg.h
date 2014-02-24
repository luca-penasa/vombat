#ifndef COMPUTESTRATIGRAPHICPOSITIONDLG_H
#define COMPUTESTRATIGRAPHICPOSITIONDLG_H

#include <QDialog>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <ui_ComputeStratigraphicPositionDlg.h>


class BaseFilter;
class ccHObject;
class ccPointCloud;




class ComputeStratigraphicPositionDlg : public QDialog, public Ui::ComputeStratigraphicPositionDlg
{
    Q_OBJECT
    
public:


    explicit ComputeStratigraphicPositionDlg(QWidget *parent = 0);

    ~ComputeStratigraphicPositionDlg();




private:
    Ui::ComputeStratigraphicPositionDlg *ui;




};

#endif // COMPUTESTRATIGRAPHICPOSITIONDLG_H
