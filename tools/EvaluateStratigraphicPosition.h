#ifndef EVALUATESTRATIGRAPHICPOSITION_H
#define EVALUATESTRATIGRAPHICPOSITION_H

#include <BaseFilter.h>
#include <dialogs/FastCloudSelectionDlg.h>

#include <spc/stratigraphy/single_attitude_model.h>

#include <ccoutofcore/ccSingleAttitudeModel.h>


class EvaluateStratigraphicPosition : public BaseFilter
{
public:    
    EvaluateStratigraphicPosition(ccPluginInterface * parent_plugin = 0);


    virtual int compute() ;

protected:
    virtual int checkSelected();

    int openInputDialog();

private:
    FastCloudSelectionDlg * m_dialog;

    ccSingleAttitudeModel * m_model;
};

#endif // EVALUATESTRATIGRAPHICPOSITION_H
