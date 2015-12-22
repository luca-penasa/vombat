#ifndef LOAD_SPC_ELEMENT_H
#pragma once
#define LOAD_SPC_ELEMENT_H

#include "BaseFilter.h"
namespace spc {
spcFwdDeclSharedPtr(ElementBase)
}

class LoadSPCElement: public BaseFilter
{
public:
    LoadSPCElement(ccPluginInterface * parent_plugin);


    //  \todo we should use a unified factory for this
    // the the ccVombatObjectsFactory
    static ccHObject * elementToCCHobject(spc::ElementBasePtr el);

    static void rebuildMyChildsRecursive(ccHObject * newobj);


    static std::vector<ccHObject *> rebuildMyChilds(ccHObject *parent);

    virtual int compute ();

    virtual int openInputDialog();

    virtual int checkSelected()
    {
        return 1;
    }


protected:
    QStringList m_filenames;


};

#endif // OPENINCOMPOSER_H
