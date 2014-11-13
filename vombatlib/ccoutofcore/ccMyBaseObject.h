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

    virtual bool isASPC(DtiClassType * type)
    {
        return this->getSPCElement()->isA(type);
    }

    virtual bool addChild(ccHObject* child, int dependencyFlags = DP_PARENT_OF_OTHER, int insertIndex = -1) override
    {
        ccCustomHObject::addChild(child, dependencyFlags, insertIndex);

        ccMyBaseObject * asmine = dynamic_cast<ccMyBaseObject * >(child);

        if (asmine)
            this->getSPCElement()->addChild(asmine->getSPCElement());
    }

    virtual void removeChild(ccHObject* child) override
    {
            ccMyBaseObject::removeChild(child);


            ccMyBaseObject * asmine = dynamic_cast<ccMyBaseObject * >(child);


            if(asmine)
                this->getSPCElement()->removeChild(asmine->getSPCElement());
    }

    virtual void detachChild(ccHObject * child) override
    {
        ccMyBaseObject::detachChild(child);

        ccMyBaseObject * asmine = dynamic_cast<ccMyBaseObject * >(child);

        if(asmine)
            this->getSPCElement()->removeChild(asmine->getSPCElement());
    }





};

#endif // CCMYBASEOBJECT_H
