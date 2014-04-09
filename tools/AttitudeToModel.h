#ifndef ATTITUDE_TO_MDOEL_H
#define ATTITUDE_TO_MDOEL_H

#include <BaseFilter.h>
#include <dialogs/FastCloudSelectionDlg.h>

#include <spc/stratigraphy/single_attitude_model.h>

#include <ccoutofcore/ccSingleAttitudeModel.h>


class AttitudeToModel : public BaseFilter
{
public:    
    AttitudeToModel(ccPluginInterface * parent_plugin = 0);


    virtual int compute() ;

protected:
    virtual int checkSelected();

//    int openInputDialog();

private:
    FastCloudSelectionDlg * m_dialog;

    ccSingleAttitudeModel * m_model;
};

#endif // ATTITUDE_TO_MDOEL_H
