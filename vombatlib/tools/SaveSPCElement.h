#pragma once
#ifndef SAVE_SPC_ELEMENT_H
#define SAVE_SPC_ELEMENT_H

#include "BaseFilter.h"

class SaveSPCElement : public BaseFilter {
public:
    SaveSPCElement(ccPluginInterface* parent_plugin);

    virtual int compute();

    virtual int openInputDialog();

    virtual int checkSelected();

protected:
    QString m_filename;
    QString m_filter;
};

#endif // SAVE_SPC_ELEMENT_H
