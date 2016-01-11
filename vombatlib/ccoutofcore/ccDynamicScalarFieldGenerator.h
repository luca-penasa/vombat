#pragma once
#ifndef CC_DYNAMIC_SCALAR_FIELD_GENERATOR_H
#define CC_DYNAMIC_SCALAR_FIELD_GENERATOR_H

#include <ccHObject.h>

#include <spc/elements/VariableScalarFieldBase.h>

#include <ccCylinder.h>
#include <ccoutofcore/ccEditableHObject.h>

#include <QDialog>

#include <ccoutofcore/ccSPCElementShell.h>
#include <QIcon>
#include <ccPointCloud.h>

#include <helpers/ccSPCObjectsStreamer.h>

#include <ccoutofcore/ccAttitude.h>

class ccDynamicScalarFieldGenerator: public ccSPCElementShell
{
    Q_OBJECT

public:

//    ccDynamicScalarFieldGenerator(): ccSPCElementShell()
//    {

//    }

    ccDynamicScalarFieldGenerator(spc::VariableScalarFieldBase::Ptr other): ccSPCElementShell(other)
    {
        m_generator_ = other;

    }

    spc::VariableScalarFieldBase::Ptr getGenerator() const
    {
        return m_generator_;
    }


    virtual bool isSerializable() const { return true; }

//    virtual bool hasColors() const { return true; }

    virtual ccBBox getMyOwnBB() {return ccBBox();}

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/SFGenerator.png"));
    }

protected:
    spc::VariableScalarFieldBase::Ptr m_generator_;




    // ccSPCElementShell interface

    // ccHObject interface
protected:
    virtual bool toFile_MeOnly(QFile &out) const
    {
        ccCustomHObject::toFile_MeOnly(out);
        ccSPCObjectsStreamer::WriteToQFile(m_generator_, out);
        return true;
    }
    virtual bool fromFile_MeOnly(QFile &in, short dataVersion, int flags)
    {
        ccCustomHObject::fromFile_MeOnly(in, dataVersion, flags);
        spc::ISerializable::Ptr el = ccSPCObjectsStreamer::ReadFromQFile( in );
        m_generator_ = spcDynamicPointerCast<spc::VariableScalarFieldBase>(el);
        return true;
    }


    // ccSerializableObject interface
};



#endif // CC_SINGLE_ATTITUDE_MODEL_H
