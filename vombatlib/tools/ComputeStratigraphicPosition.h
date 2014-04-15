#ifndef COMPUTESTRATIGRAPHICPOSITION_H
#define COMPUTESTRATIGRAPHICPOSITION_H


//#include <BaseFilter.h>
#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <dialogs/ComputeStratigraphicPositionDlg.h>

#include <Eigen/Dense>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>


class ComputeStratigraphicPosition : public BaseFilter
{

public:

    ComputeStratigraphicPosition(ccPluginInterface * parent_plugin = 0);

public:
    int compute() ;

    int openInputDialog();

    void getParametersFromDialog();


private:
    ComputeStratigraphicPositionDlg * m_dialog;

    ccHObject *m_obj;


};

#endif // COMPUTESTRATIGRAPHICPOSITION_H
