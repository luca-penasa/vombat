#ifndef CCMYBASEOBJECT_H
#define CCMYBASEOBJECT_H

#include <ccoutofcore/ccEditableHObject.h>
#include <ccHObject.h>
#include <dialogs/ccTimeSeriesGeneratorEditorDlg.h>

#include <spc/elements/element_base.h>
//#include <boost/serialization/string.hpp>

#include <ccCustomObject.h>

/// teach boost how to serialize QString -  using a std::string
//namespace boost
//{

//namespace serialization {
//
//template<class Archive>
//inline void load(
//        Archive & ar,
//        QString& t,
//        const unsigned int file_version
//        )
//{
//    std::string tmp;
//    ar >> boost::serialization::make_nvp("string", tmp);
//
//    t = QString::fromStdString(tmp);
//
//}
//
//template<class Archive>
//inline void save(
//        Archive & ar,
//        const QString& t,
//        const unsigned int file_version
//        )
//{
//    std::string standard = t.toStdString();
//    ar << boost::serialization::make_nvp("string", standard);
//}



//} //end nspace serialization
//}//end nspace boost


//BOOST_SERIALIZATION_SPLIT_FREE(QString)




class ccMyBaseObject: public ccEditableHObject, public ccCustomHObject
{
                                 public:
                                 ///
                                 /// \brief ccMyBaseObject def constructor
                                 ///
                                 ccMyBaseObject();

//protected:
//friend class boost::serialization::access;
//
//template <class Archive>
//void serialize(Archive &ar, const unsigned int version)
//{
//    //        ar & BOOST_SERIALIZATION_NVP(m_scale);
//    //        ar & BOOST_SERIALIZATION_NVP(m_width);
//    //        ar & boost::serialization::make_nvp("spcAttitude", boost::serialization::base_object<spc::spcAttitude> (*this));
//    //        ar & boost::serialization::make_nvp("ccMyBaseObject", boost::serialization::base_object<ccMyBaseObject> (*this));
//
//
//    ar & BOOST_SERIALIZATION_NVP(m_visible);
//    ar & BOOST_SERIALIZATION_NVP(m_colorsDisplayed);
//    ar & BOOST_SERIALIZATION_NVP(m_showNameIn3D);
//    ar & BOOST_SERIALIZATION_NVP(m_name);
//
//
//
//}


//virtual bool isSerializable() const { return false; }

//virtual bool hasColors() const { return false; }



};

#endif // CCMYBASEOBJECT_H
