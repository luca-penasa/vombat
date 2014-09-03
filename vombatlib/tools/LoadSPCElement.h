#ifndef LOAD_SPC_ELEMENT_H
#define LOAD_SPC_ELEMENT_H

#include <qPCL/PclUtils/filters/BaseFilter.h>

#include <vombat.h>

#include <ccoutofcore/ccMyBaseObject.h>
#include<ccoutofcore/ccAttitude.h>
#include <ccoutofcore/ccEigenTable.h>
#include <ccoutofcore/ccSample.h>
//#include <ccoutofcore/ccSingleAttitudeModel.h>




class LoadSPCElement: public BaseFilter
{
public:
    LoadSPCElement(ccPluginInterface * parent_plugin);

    virtual int compute ()
    {
        spc::ISerializable::Ptr obj = spc::io::deserializeFromFile(m_filename.toStdString());

        if (!obj)
            return -1;

        spc::ElementBase::Ptr el = spcDynamicPointerCast<spc::ElementBase> (obj);

        if (!el)
            return -1;

        ccHObject * newobj;
        if (el->getType() == &spc::Attitude::Type)
        {
            spc::Attitude::Ptr att = spcDynamicPointerCast<spc::Attitude>(el);
            newobj = new ccAttitude(att);
        }
        else if (el->getType() == &spc::EigenTable::Type)
        {
            spc::EigenTable::Ptr att = spcDynamicPointerCast<spc::EigenTable>(el);
            newobj = new ccEigenTable(att);
        }
        else if (el->getType() == &spc::Sample::Type)
        {
            spc::Sample::Ptr att = spcDynamicPointerCast<spc::Sample>(el);
            newobj = new ccSample(att);
        }
        else
        {
            return -1;
        }




        newobj->setEnabled(true);
        newobj->setVisible(true);


//        entityHasChanged(newobj);
        newEntity(newobj);

        return 1;
    }

    virtual int openInputDialog()
    {
        m_filename.clear();
        m_filename =  QFileDialog::getOpenFileName(0, tr("Load From XML File"),
                                                   "",
                                                   tr("XML Documents (*.xml)"));
        if (m_filename.isEmpty())
            return -1;

        return 1;
    }

    virtual int checkSelected()
    {
        return 1;
    }


protected:
    QString m_filename;


};

#endif // OPENINCOMPOSER_H
