#pragma once
#ifndef EDIT_H
#define EDIT_H

#include <BaseFilter.h>

class Edit : public BaseFilter {
public:
    Edit(ccPluginInterface* parent_plugin = 0);

    virtual int compute();

protected:
    virtual int checkSelected();

    //    int openInputDialog();

private:
    //    FastCloudSelectionDlg * m_dialog;

    //    ccSingleAttitudeModel * m_model;
};

#endif // EDIT_H
