#ifndef LOAD_SPC_ELEMENT_H
#define LOAD_SPC_ELEMENT_H

#include <qPCL/PclUtils/filters/BaseFilter.h>

#include <vombat.h>

#include <ccoutofcore/ccMyBaseObject.h>
#include<ccoutofcore/ccAttitude.h>
#include <ccoutofcore/ccEigenTable.h>
#include <ccoutofcore/ccSample.h>
//#include <ccoutofcore/ccSingleAttitudeModel.h>

#include <ccPlanarSelection.h>




class LoadSPCElement: public BaseFilter
{
public:
    LoadSPCElement(ccPluginInterface * parent_plugin);

    virtual int compute ()
    {

    spc::io::testXMLMatrixWrite();

//{

//    Eigen::Vector3f normal, position;
//    normal = Eigen::Vector3f::Random();
//    position = Eigen::Vector3f::Random();
//    spc::Attitude::Ptr att(new spc::Attitude);
//    att->setNormal(normal);
//    att->setPosition(position);

//    std::cout << att->getNormal() << std::endl;
//    std::cout << att->getPosition() << std::endl;

//    spc::io::serializeToFile(att, "/home/luca/attitude", spc::io::JSON);

//}

//    {
//    spc::ISerializable::Ptr reloaded =  spc::io::deserializeFromFile("/home/luca/attitude.json");
//    spc::Attitude::Ptr newatt = spcDynamicPointerCast<spc::Attitude> (reloaded);

//    std::cout << newatt->getNormal() << std::endl;
//    std::cout << newatt->getPosition() << std::endl;

//    spc::io::serializeToFile(newatt, "/home/luca/attitude2", spc::io::JSON);
//    }





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
        else if (el->getType() ==&spc::SelectionRubberband::Type)
        {
            spc::SelectionRubberband::Ptr att = spcDynamicPointerCast<spc::SelectionRubberband> (el);
            newobj = new ccPlanarSelection(att);
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
