#ifndef ATTITUDE_TO_MODEL_H
#define ATTITUDE_TO_MODEL_H

//#include <BaseFilter.h>
#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <dialogs/FastCloudSelectionDlg.h>

#include <spc/stratigraphy/single_attitude_model.h>

#include <ccoutofcore/ccSingleAttitudeModel.h>


class AttitudeToModel : public BaseFilter
{
public:    
    AttitudeToModel(ccPluginInterface * parent_plugin = 0);

    ~AttitudeToModel()
    {
        //we must delete parent-less dialogs ourselves!
        if (m_dialog && m_dialog->parent() == 0)
            delete m_dialog;
    }


    virtual int compute() ;

protected:
    virtual int checkSelected();

//    int openInputDialog();

private:
    FastCloudSelectionDlg * m_dialog;

    ccSingleAttitudeModel * m_model;
};

#endif // ATTITUDE_TO_MDOEL_H
