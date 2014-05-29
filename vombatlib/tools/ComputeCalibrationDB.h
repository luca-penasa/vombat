#ifndef COMPUTE_CALIBRATION_DB_H
#define COMPUTE_CALIBRATION_DB_H

//#include <BaseFilter.h>
#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <dialogs/ccCalibrateDeviceDlg.h>

#include <dialogs/ComputeCalibrationDBDlg.h>

#include <spc/elements/IntensityCalibration/DataDB.h>


class ComputeCalibrationDB: public BaseFilter
{
public:
    ComputeCalibrationDB(ccPluginInterface * parent_plugin = 0);

    ~ComputeCalibrationDB()
    {
        //we must delete parent-less dialogs ourselves!
        if (m_dialog && m_dialog->parent() == 0)
            delete m_dialog;
    }

    virtual int compute() ;


protected:
    virtual int checkSelected();

    virtual int openInputDialog();

    ComputeCalibrationDBDlg * m_dialog;



};

#endif // COMPUTE_CALIBRATION_DB_H
