#ifndef COMPUTESTRATIGRAPHICPOSITIONDLG_H
#define COMPUTESTRATIGRAPHICPOSITIONDLG_H

#include <QDialog>

//#include <pcl/point_cloud.h>
//#include <pcl/point_types.h>
#include <ui_EvaluateDynamicScalarFieldGeneratorDlg.h>


class BaseFilter;
class ccHObject;
class ccPointCloud;




class EvaluateDynamicScalarFieldGeneratorDlg : public QDialog, public Ui::EvaluateDynamicScalarFieldGeneratorDlg
{
    Q_OBJECT
    
public:


    explicit EvaluateDynamicScalarFieldGeneratorDlg(QWidget *parent = 0);

    ~EvaluateDynamicScalarFieldGeneratorDlg();







    Ui::EvaluateDynamicScalarFieldGeneratorDlg *ui;




};

#endif // COMPUTESTRATIGRAPHICPOSITIONDLG_H
