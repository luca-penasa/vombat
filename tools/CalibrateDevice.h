#ifndef CALIBRATEDEVICE_H
#define CALIBRATEDEVICE_H

//#include <BaseFilter.h>
#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <dialogs/ccCalibrateDeviceDlg.h>

class CalibrateDevice: public BaseFilter
{
public:
    CalibrateDevice(ccPluginInterface * parent_plugin = 0);


    virtual int compute() ;

protected:
    virtual int checkSelected();

    virtual int openInputDialog();

    ccCalibrateDeviceDlg * m_dialog;

};

#endif // CALIBRATEDEVICE_H
