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

    ccMyBaseObject(spc::ElementBase::Ptr el)
    {
        m_name = el->getElementName().c_str();
    }

    virtual spc::ElementBase::Ptr getSPCElement() const = 0;

    // each derived object should implement one
    virtual QString getSPCClassName() const;

    virtual void writeSPCClassNameToMetadata();

    virtual bool isASPC(DtiClassType * type)
    {
        return this->getSPCElement()->isA(type);
    }

    virtual bool addChild(ccHObject* child, int dependencyFlags = DP_PARENT_OF_OTHER, int insertIndex = -1) override;

    virtual void removeChild(ccHObject* child) override;

    virtual void removeChild(int pos) override;


    virtual  void setParent(ccHObject* anObject) override;



    virtual void detachChild(ccHObject * child) override;


    //! Sets object name
    virtual void setName(const QString& name) override;



};

#endif // CCMYBASEOBJECT_H
