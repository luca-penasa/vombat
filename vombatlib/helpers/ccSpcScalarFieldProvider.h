#pragma once
#ifndef CCSPCSCALARFIELDPROVIDER_H
#define CCSPCSCALARFIELDPROVIDER_H

#include <spc/elements/FieldProviderBase.h>

#include <ccScalarField.h>
//#include <ccPointCloud.h>
//#include <GenericChunkedArray.h>
#include <ScalarField.h>
#include <CCTypes.h>

class ccSpcScalarFieldProvider: public spc::FieldProviderBase<ScalarType>
{
public:
    ccSpcScalarFieldProvider(ccScalarField * field)
    {
        field_ = field;
    }

    virtual ~ccSpcScalarFieldProvider()
    {

    }

    // FieldProviderBase interface
public:
    virtual void resize(const size_t &n_elements) override
    {
        field_->resize(n_elements);
    }
    virtual ScalarType *data() override
    {
        return field_->data();
    }
    virtual size_t getFieldDimension() const override
    {
        return 1;
    }
    virtual size_t getNumberOfElements() const override
    {
        return field_->currentSize();
    }
    virtual std::string getFieldName() const override
    {
        return field_->getName();
    }
    virtual void setFieldName(const std::string &name) override
    {
        field_->setName(name.c_str());
    }

protected:
    ccScalarField * field_;
};

#endif // CCSPCSCALARFIELDPROVIDER_H
