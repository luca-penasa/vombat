#pragma once
#ifndef ATTITUDE_TO_MODEL_H
#define ATTITUDE_TO_MODEL_H

#include "BaseFilter.h"

class ccHObjectSelectionDlgSimple;
class ccSingleAttitudeModel;

class AttitudeToModel : public BaseFilter {
public:
    AttitudeToModel(ccPluginInterface* parent_plugin = 0);

    ~AttitudeToModel();

    virtual int compute();

protected:
    virtual int checkSelected();

    //    int openInputDbialog();

private:
    ccHObjectSelectionDlgSimple* m_dialog;

    ccSingleAttitudeModel* m_model;
};

#endif // ATTITUDE_TO_MDOEL_H
