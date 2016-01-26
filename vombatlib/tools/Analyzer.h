#pragma once
#ifndef ANALYZER_H
#define ANALYZER_H

#include "BaseFilter.h"

class AnalyzerDlg;
class ccVirtualOutcrop;

class Analyzer : public BaseFilter {
public:
    Analyzer(ccPluginInterface* parent_plugin = 0);

    // BaseFilter interface
public:
    int compute();


//    static void linkPolylinesToConstraints(ccHObject::Container links_polys, ccHObject::Container )
protected:
    int checkSelected();

    int openInputDialog();


    AnalyzerDlg * m_dialog;

    ccVirtualOutcrop * m_root_outcrop;
};

#endif // ANALYZER_H
