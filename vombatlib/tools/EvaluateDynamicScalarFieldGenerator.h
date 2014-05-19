#pragma once
#ifndef EVALUATE_DYNAMIC_SCALAR_FIELD_GENERATOR_H
#define EVALUATE_DYNAMIC_SCALAR_FIELD_GENERATOR_H

#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <dialogs/ccHObjectSelectionDlgSimple.h>
#include <spc/scalar_fields_generators/single_attitude_model.h>
#include <ccoutofcore/ccSingleAttitudeModel.h>

#include <EvaluateDynamicScalarFieldGeneratorDlg.h>

class EvaluateDynamicScalarFieldGenerator : public BaseFilter
{
public:    
    EvaluateDynamicScalarFieldGenerator(ccPluginInterface * parent_plugin = 0);


    virtual int compute() ;

protected:
    virtual int checkSelected();

    int openInputDialog();


   EvaluateDynamicScalarFieldGeneratorDlg * m_dialog;

    ccDynamicScalarFieldGenerator * m_generator;
};

#endif // end guard
