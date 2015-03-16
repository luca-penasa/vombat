#ifndef SAVE_SPC_ELEMENT_H
#define SAVE_SPC_ELEMENT_H

#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <vombat.h>
#include <spc/elements/ElementBase.h>

#include <ccoutofcore/ccSPCElementShell.h>
#include <ccoutofcore/ccAttitude.h>
//#include <boost/typeof/typeof.hpp>

#include <spc/io/element_io.h>

#include <iostream>


#include <QFileDialog>

class SaveSPCElement : public BaseFilter
{
public:
    SaveSPCElement(ccPluginInterface *parent_plugin);

    virtual int compute()
    {


        // only the first one
        ccHObject *qua = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::ElementBase::Type).at(0);
        ccSPCElementShell *my = dynamic_cast<ccSPCElementShell *>(qua);

        if (!my)
        {
            LOG(ERROR) << "cannot dynamic cast to ccSPCElementShell. This Should never happen!";
            return -1;

        }

        spc::ElementBase::Ptr element = my->getSPCElement();

        if (!element)
        {
            LOG(ERROR) << "Returned element is null!";
            return -1;
        }

        spc::io::serializeToFile(element, m_filename.toStdString(), spc::io::XML);

        return 1;
    }

    virtual int openInputDialog()
    {
        m_filename.clear();
        m_filename = QFileDialog::getSaveFileName(0, tr("Save To XML File"), "",
                                                  tr("XML Documents (*.xml)"));

        if (m_filename.isEmpty())
            return -1;

        return 1;
    }

    virtual int checkSelected()
    {

        ccHObject::Container all = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::ElementBase::Type);

        for (ccHObject * oj: all)
            LOG(INFO) << "selected: " << oj->getName().toStdString();

        if (all.size() == 1) // one at a time for now
            return 1;
        else
            return -1;

    }

protected:
    QString m_filename;
};

#endif // SAVE_SPC_ELEMENT_H
