#ifndef SAVE_SPC_ELEMENT_H
#define SAVE_SPC_ELEMENT_H

#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <vombat.h>
#include <spc/elements/ElementBase.h>

#include <ccoutofcore/ccMyBaseObject.h>
#include <ccoutofcore/ccAttitude.h>
//#include <boost/typeof/typeof.hpp>

#include <spc/io/element_io.h>

#include <iostream>

class SaveSPCElement : public BaseFilter
{
public:
    SaveSPCElement(ccPluginInterface *parent_plugin);

    virtual int compute()
    {

        ccHObject *qua = getSelectedThatHaveMetaData("plugin_name", "vombat").at(0);

        ccMyBaseObject *my = dynamic_cast<ccMyBaseObject *>(qua);

        if (!my)
        {
            return -1;
        }

        spc::ElementBase::Ptr element = my->getSPCElement();

        if (!element)
        {
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

        ccHObject::Container all = getSelectedThatHaveMetaData("plugin_name", "vombat");

        if (all.size() != 1) // one at a time for now
            return -1;

        else
            return 1;

    }

protected:
    QString m_filename;
};

#endif // SAVE_SPC_ELEMENT_H
