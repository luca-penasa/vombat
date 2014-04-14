#ifndef EDIT_H
#define EDIT_H

//#include <BaseFilter.h>
#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <dialogs/FastCloudSelectionDlg.h>


#include <ccoutofcore/ccSingleAttitudeModel.h>


class Edit : public BaseFilter
{
public:    
    Edit(ccPluginInterface * parent_plugin = 0);


    virtual int compute() ;

protected:
    virtual int checkSelected();

//    int openInputDialog();

private:
//    FastCloudSelectionDlg * m_dialog;

//    ccSingleAttitudeModel * m_model;
};

#endif // EDIT_H
