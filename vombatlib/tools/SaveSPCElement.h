//#ifndef SAVE_SPC_ELEMENT_H
//#define SAVE_SPC_ELEMENT_H
//
//#include <BaseFilter.h>
//#include <vombat.h>
//#include <dialogs/Composer.h>
//#include <spc/elements/element_base.h>
//
//
//#include <ccoutofcore/ccMyBaseObject.h>
//#include<ccoutofcore/ccAttitude.h>
//#include <boost/typeof/typeof.hpp>
//
//#include <spc/elements/spcSerializableContainer.h>
//
//#include <spc/io/element_io.h>
//
//#include <boost/foreach.hpp>
//
//
//
//class SaveSPCElement: public BaseFilter
//{
//public:
//    SaveSPCElement(ccPluginInterface * parent_plugin);
//
//    virtual int compute ()
//    {
//        return 1;
//    }
//
//
//    virtual int openOutputDialog()
//    {
//        if (m_filename.isEmpty())
//            return 1;
//
//        // get all qgeo-valid objects that are also selected
//        ccHObject::Container all = vombat::theInstance()->getSelectedThatHaveMetaData("[vombat]");
//
//        BOOST_FOREACH(ccHObject * obj, all)
//        {
//            std::cout << obj->getName().toStdString().c_str() << std::endl;
//        }
//
//        spc::spcSerializableContainer::Ptr all_objects =  spc::spcSerializableContainer::Ptr(new spc::spcSerializableContainer);
//
//
//
//        BOOST_FOREACH (ccHObject * obj, all)
//        {
//
//            spc::spcSerializableObject * element = dynamic_cast<spc::spcSerializableObject *> (obj);
//
//            if (!element)
//            {
//                std::cout << "skipped element!" << std::endl;
//                continue;
//            }
//
//
//
//            all_objects->push_back(element);
//        }
//
//
//        //now serialize everything!
//
//        spc::spcElementSerializer serializer;
//        bool status = serializer.save(m_filename.toStdString(), all_objects);
//
//        if (!status)
//        {
//            ccLog::Error("Some error eccured trying to save the objects!");
//            return -1;
//        }
//
//
//
//        return 1;
//    }
//
//    virtual int openInputDialog()
//    {
//        m_filename.clear();
//        m_filename =  QFileDialog::getSaveFileName(0, tr("Save To XML File"),
//                                                   "",
//                                                   tr("XML Documents (*.xml)"));
//
//        return 1;
//    }
//
//    virtual int checkSelected()
//    {
//        ccHObject::Container qua = vombat::theInstance()->getSelectedThatHaveMetaData("[vombat]");
//
//        if (qua.size() > 0)
//        {
//            return 1;
//        }
//        else
//            return -1;
//    }
//
//
//protected:
//    QString m_filename;
//
//
//};
//
//#endif // SAVE_SPC_ELEMENT_H