#ifndef ccSPCElementShell_H
#define ccSPCElementShell_H

#include <ccoutofcore/ccEditableHObject.h>
#include <ccHObject.h>

#include <ccCustomObject.h>
#include <spc/elements/ElementBase.h>
#include <helpers/ccSPCObjectsStreamer.h>


//!
//! \brief The ccSPCElementShell class
//! empty constructor is not allowed. Each object must be the shell of some kind of spc element
//! This grant consistency
//! If you need to create objects which are not shells of any spc element just use a ccCustomHObject
//! \note ccEditableHObject interface will be soon dropped
class ccSPCElementShell : public ccEditableHObject, public ccCustomHObject
{
public:
    ccSPCElementShell(spc::ElementBase::Ptr el, const QString & name = QString("")): ccCustomHObject(name)
    {

        LOG(INFO) << " ccSPCElementShell constructor called!";

//        CHECK(el !=nullptr);

        if (el !=nullptr)
        {
            element_ = el;

            updateCcDataFromSpc();
        }

        DLOG(INFO) << "ccSPCElementShell correctly initialized";
    }


    void updateCcDataFromSpc()
    {
        // force the name to match the one in the element
        setName(element_->getElementName().c_str());

        writeSPCClassNameToMetadata();
    }


    spc::ElementBase::Ptr getSPCElement() const
    {
        return element_;
    }

    //! if a conversion is available it will return the element
    //! as a ElementT type
    template <typename ElementT>
    typename ElementT::Ptr getSPCElement() const
    {
        return spcDynamicPointerCast<ElementT>(element_);
    }

    // each derived object should implement one
   QString getSPCClassName() const
    {
       DLOG(INFO) << "asked spcclassname, returned: " <<  element_->getClassNameFromDtiClass();
        return QString::fromStdString(element_->getClassNameFromDtiClass());

    }
private:
    virtual void writeSPCClassNameToMetadata();

public:
    virtual bool isASPC(DtiClassType * type)
    {
        return this->getSPCElement()->isA(type);
    }


   //! overrides of ccHObject and ccObject
    virtual bool addChild(ccHObject* child, int dependencyFlags = DP_PARENT_OF_OTHER, int insertIndex = -1) override;

    virtual void removeChild(ccHObject* child) override;

    virtual void removeChild(int pos) override;

    virtual  void setParent(ccHObject* anObject) override;

    virtual void detachChild(ccHObject * child) override;

    virtual void setName(const QString& name) override;

private:
    spc::ElementBase::Ptr element_;


protected:
    virtual bool toFile_MeOnly(QFile &out) const
    {
        ccCustomHObject::toFile_MeOnly(out);
        ccSPCObjectsStreamer::WriteToQFile(element_, out);
        return true;
    }
    virtual bool fromFile_MeOnly(QFile &in, short dataVersion, int flags)
    {
        ccCustomHObject::fromFile_MeOnly(in, dataVersion, flags);
        spc::ISerializable::Ptr el = ccSPCObjectsStreamer::ReadFromQFile(in);
        element_ = spcDynamicPointerCast<spc::ElementBase>(el);

        CHECK(element_ != nullptr); // security assert

        updateCcDataFromSpc();

        return true;
    }




    // ccHObject interface
protected:
    virtual void applyGLTransformation(const ccGLMatrix &trans) override;
};

#endif // ccSPCElementShell_H
