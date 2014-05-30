#ifndef CC_DYNAMIC_SCALAR_FIELD_GENERATOR_H
#define CC_DYNAMIC_SCALAR_FIELD_GENERATOR_H

#include <ccHObject.h>

#include <spc/elements/VariableScalarFieldBase.h>

#include <ccCylinder.h>
#include <ccoutofcore/ccEditableHObject.h>

#include <QDialog>

#include <ccoutofcore/ccMyBaseObject.h>
#include <QIcon>
#include <ccPointCloud.h>


#include <ccoutofcore/ccAttitude.h>

class ccDynamicScalarFieldGenerator: public QObject,  public ccMyBaseObject
{
    Q_OBJECT

public:


    ccDynamicScalarFieldGenerator(const char * name =0): ccMyBaseObject(name)
    {


    }

    // copy const
    ccDynamicScalarFieldGenerator(const ccDynamicScalarFieldGenerator &other)
    {
        m_generator_ = other.getGenerator();
    }

    // construct passing an spc::DynamicScalarFieldgenerator pointer
    ccDynamicScalarFieldGenerator(const spc::VariableScalarFieldBase::Ptr &other)
    {
        m_generator_ = other;
    }

    spc::VariableScalarFieldBase::Ptr getGenerator() const
    {
        return m_generator_;
    }

    virtual QString getSPCClassName() const
    {
        return "ccDynamicScalarFieldGenerator";
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



};



#endif // CC_SINGLE_ATTITUDE_MODEL_H
