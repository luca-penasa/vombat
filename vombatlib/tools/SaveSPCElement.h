//#ifndef SAVE_SPC_ELEMENT_H
//#define SAVE_SPC_ELEMENT_H

//#include <qPCL/PclUtils/filters/BaseFilter.h>
//#include <vombat.h>
//#include <spc/elements/ElementBase.h>


//#include <ccoutofcore/ccMyBaseObject.h>
//#include<ccoutofcore/ccAttitude.h>
////#include <boost/typeof/typeof.hpp>



//#include <spc/io/element_io.h>


//#include <iostream>

//class SaveSPCElement: public BaseFilter
//{
//public:
//    SaveSPCElement(ccPluginInterface * parent_plugin);

//    virtual int compute ()
//    {
//        return 1;
//    }


//    virtual int openOutputDialog()
//    {
//        if (m_filename.isEmpty())
//            return 1;

//        // get all vombat-valid objects that are also selected
//        ccHObject::Container all = vombat::theInstance()->getSelectedThatHaveMetaData("[vombat]");

//        spcForEachMacro(ccHObject * obj, all)
//        {
//            std::cout << obj->getName().toStdString().c_str() << std::endl;
//        }

//        spc::spcSerializableContainer::Ptr all_objects =  spc::spcSerializableContainer::Ptr(new spc::spcSerializableContainer);



//        spcForEachMacro (ccHObject * obj, all)
//        {

//            spc::spcSerializableObject * element = dynamic_cast<spc::spcSerializableObject *> (obj);

//            if (!element)
//            {
//                std::cout << "skipped element!" << std::endl;
//                continue;
//            }



//            all_objects->push_back(spcMakeSharedPtrMacro<spc::spcSerializableObject> (*element));
//        }


//        //now serialize everything!

//        spc::ElementsIO serializer;
//        bool status = serializer.serializeToFile(all_objects, m_filename.toStdString());

//        if (!status)
//        {
//            ccLog::Error("Some error eccured trying to save the objects!");
//            return -1;
//        }



//        return 1;
//    }

//    virtual int openInputDialog()
//    {
//        m_filename.clear();
//        m_filename =  QFileDialog::getSaveFileName(0, tr("Save To XML File"),
//                                                   "",
//                                                   tr("XML Documents (*.xml)"));

//        return 1;
//    }

//    virtual int checkSelected()
//    {

//        ccHObject::Container qua = getSelectedThatHaveMetaData("vombat");
//        return qua.size();
//    }


//protected:
//    QString m_filename;


//};

//#endif // SAVE_SPC_ELEMENT_H
