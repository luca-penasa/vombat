#ifndef CC_DYNAMIC_SCALAR_FIELD_GENERATOR_H
#define CC_DYNAMIC_SCALAR_FIELD_GENERATOR_H

#include <ccHObject.h>

#include <spc/scalar_fields_generators/DynamicScalarFieldGenerator.h>

#include <ccCylinder.h>
#include <ccoutofcore/ccEditableHObject.h>

#include <QDialog>

#include <ccoutofcore/ccMyBaseObject.h>
#include <QIcon>
#include <ccPointCloud.h>

#include <spc/elements/salvable_object.h> //needed to serialize Vector3f

#include <ccoutofcore/ccAttitude.h>

class ccDynamicScalarFieldGenerator: public QObject,  public ccMyBaseObject
{
    Q_OBJECT

public:


    ccDynamicScalarFieldGenerator()
    {
        initMetadata();
    }

    // copy const
    ccDynamicScalarFieldGenerator(const ccDynamicScalarFieldGenerator &other)
    {
        m_generator_ = other.getGenerator();
        initMetadata();

    }

    // construct passing an spc::DynamicScalarFieldgenerator pointer
    ccDynamicScalarFieldGenerator(const spc::DynamicScalarFieldGenerator::Ptr &other)
    {
        m_generator_ = other;
        initMetadata();

    }

    spc::DynamicScalarFieldGenerator::Ptr getGenerator() const
    {
        return m_generator_;
    }



    virtual bool isSerializable() const { return true; }

//    virtual bool hasColors() const { return true; }

    virtual ccBBox getMyOwnBcB() {return ccBBox();}

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/SFGenerator.png"));
    }

protected:
    void initMetadata()
    {
        QVariant var(QString("Generic Scalar Field Generator"));

        setMetaData(QString("[vombat][ccDynamicScalarFieldGenerator]"), var);
    }



    spc::DynamicScalarFieldGenerator::Ptr m_generator_;



};



#endif // CC_SINGLE_ATTITUDE_MODEL_H
