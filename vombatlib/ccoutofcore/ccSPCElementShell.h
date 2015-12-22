#pragma once
#ifndef ccSPCElementShell_H
#define ccSPCElementShell_H

#include <ccCustomObject.h>
#include <ccEditableHObject.h>
#include <spc/core/macros_ptr.h>
#include <QIcon>

namespace spc {
spcFwdDeclSharedPtr(ElementBase)

class DtiClassType;
}


//!
//! \brief The ccSPCElementShell class
//! empty constructor is not allowed. Each object must be the shell of some kind of spc element
//! This grant consistency
//! If you need to create objects which are not shells of any spc element just use a ccCustomHObject
//! \note ccEditableHObject interface will be soon dropped
class ccSPCElementShell : public ccEditableHObject, public ccCustomHObject {
public:
    ccSPCElementShell(spc::ElementBasePtr el, const QString& name = QString(""));

    void updateCcDataFromSpc();

    spc::ElementBasePtr getSPCElement() const;

    //! if a conversion is available it will return the element
    //! as a ElementT type
    template <typename ElementT>
    typename ElementT::Ptr getSPCElement() const
    {
        return spcDynamicPointerCast<ElementT>(element_);
    }

    // each derived object should implement one
    QString getSPCClassName() const;

private:
    virtual void writeSPCClassNameToMetadata();

public:
    virtual bool isASPC(spc::DtiClassType* type);

    //! overrides of ccHObject and ccObject
    virtual bool addChild(ccHObject* child, int dependencyFlags = DP_PARENT_OF_OTHER, int insertIndex = -1) override;

    virtual void removeChild(ccHObject* child) override;

    virtual void removeChild(int pos) override;

    virtual void setParent(ccHObject* anObject) override;

    virtual void detachChild(ccHObject* child) override;

    virtual void setName(const QString& name) override;

private:
    spc::ElementBasePtr element_;

protected:
    virtual bool toFile_MeOnly(QFile& out) const;
    virtual bool fromFile_MeOnly(QFile& in, short dataVersion, int flags);

    // ccHObject interface
protected:
    virtual void applyGLTransformation(const ccGLMatrix& trans) override;
};

#endif // ccSPCElementShell_H
