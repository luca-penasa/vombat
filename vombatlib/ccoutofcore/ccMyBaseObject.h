#ifndef CCMYBASEOBJECT_H
#define CCMYBASEOBJECT_H

#include <ccoutofcore/ccEditableHObject.h>
#include <ccHObject.h>

#include <ccCustomObject.h>
#include <spc/elements/ElementBase.h>

class ccMyBaseObject : public ccEditableHObject, public ccCustomHObject
{
public:
    ///
    /// \brief ccMyBaseObject def constructor
    ///
    ccMyBaseObject();

    ccMyBaseObject(QString name);

    virtual spc::ElementBase::Ptr getSPCElement() const = 0;

    // each derived object should implement one
    virtual QString getSPCClassName() const;

    virtual void writeSPCClassNameToMetadata();



};

#endif // CCMYBASEOBJECT_H
