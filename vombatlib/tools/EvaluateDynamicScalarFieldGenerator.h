#pragma once
#ifndef EVALUATE_DYNAMIC_SCALAR_FIELD_GENERATOR_H
#define EVALUATE_DYNAMIC_SCALAR_FIELD_GENERATOR_H

#include "BaseFilter.h"
class EvaluateDynamicScalarFieldGeneratorDlg;
class ccDynamicScalarFieldGenerator;

class EvaluateDynamicScalarFieldGenerator : public BaseFilter {
public:
    EvaluateDynamicScalarFieldGenerator(ccPluginInterface* parent_plugin = 0);

    virtual int compute();

protected:
    virtual int checkSelected();

    int openInputDialog();

    EvaluateDynamicScalarFieldGeneratorDlg* m_dialog;

    ccDynamicScalarFieldGenerator* m_generator;
};

#endif // end guard
