#ifndef CCMYBASEOBJECT_H
#define CCMYBASEOBJECT_H

#include <ccoutofcore/ccEditableHObject.h>
#include <ccHObject.h>

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



//virtual bool isSerializable() const { return false; }

//virtual bool hasColors() const { return false; }



};

#endif // CCMYBASEOBJECT_H
