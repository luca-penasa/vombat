#ifndef COMPUTE_CALIBRATION_DB_H
#define COMPUTE_CALIBRATION_DB_H

//#include <BaseFilter.h>
#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <dialogs/ccCalibrateDeviceDlg.h>

#include <dialogs/ComputeCalibrationDBDlg.h>

#include <spc/calibration/CalibrationDataDB.h>


class ComputeCalibrationDB: public BaseFilter
{
public:
    ComputeCalibrationDB(ccPluginInterface * parent_plugin = 0);


    virtual int compute() ;

protected:
    virtual int checkSelected();

    virtual int openInputDialog();

    ComputeCalibrationDBDlg * m_dialog;

    static std::vector<ccPointCloud * > CalibrationDBAsPointClouds( const spc::CalibrationDataDB &db);

};

#endif // COMPUTE_CALIBRATION_DB_H
