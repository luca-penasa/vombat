#ifndef CCMYBASEOBJECT_H
#define CCMYBASEOBJECT_H

#include <ccoutofcore/ccEditableHObject.h>
#include <ccHObject.h>

#include <ccCustomObject.h>


class ccMyBaseObject: public ccEditableHObject, public ccCustomHObject
{
public:
    ///
    /// \brief ccMyBaseObject def constructor
    ///
    ccMyBaseObject();

    ccMyBaseObject(QString name);

    //each derived object should implement one
    virtual QString getSPCClassName() const;

    virtual void writeSPCClassNameToMetadata()
    {
        QString name =  this->getSPCClassName();
        setMetaData(QString("class_name"), QVariant(QString(name)));
    }





};

#endif // CCMYBASEOBJECT_H
