#ifndef SAVE_SPC_ELEMENT_H
#define SAVE_SPC_ELEMENT_H

#include "BaseFilter.h"
#include <vombat.h>
#include <spc/elements/ElementBase.h>

#include <ccoutofcore/ccSPCElementShell.h>
#include <ccoutofcore/ccAttitude.h>
//#include <boost/typeof/typeof.hpp>

#include <spc/io/element_io.h>

#include <iostream>
#include <spc/core/file_operations.h>

#include <QFileDialog>

class SaveSPCElement : public BaseFilter
{
public:
    SaveSPCElement(ccPluginInterface *parent_plugin);

    virtual int compute();

    virtual int openInputDialog();

    virtual int checkSelected();

protected:
    QString m_filename;
    QString m_filter;
};

#endif // SAVE_SPC_ELEMENT_H
