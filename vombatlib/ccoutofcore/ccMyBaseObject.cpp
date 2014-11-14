#include "ccMyBaseObject.h"

#include <spc/elements/StratigraphicPositionableElement.h>

ccMyBaseObject::ccMyBaseObject()
{
    setMetaData(QString("plugin_name"), QVariant(QString("vombat")));

    DLOG(INFO) << "created a ccMyBaseObject";

}

ccMyBaseObject::ccMyBaseObject(QString name) : ccCustomHObject(name)
{
    setMetaData(QString("plugin_name"), QVariant(QString("vombat")));
    DLOG(INFO) << "created a ccMyBaseObject";
}

QString ccMyBaseObject::getSPCClassName() const
{
    return "ccMyBaseObject";
}

void ccMyBaseObject::writeSPCClassNameToMetadata()
{
    QString name = this->getSPCClassName();
    setMetaData(QString("class_name"), QVariant(QString(name)));
}


bool ccMyBaseObject::addChild(ccHObject *child, int dependencyFlags, int insertIndex)
{

    DLOG(INFO) << "adding child";

    ccHObject::addChild(child, dependencyFlags, insertIndex);

    ccMyBaseObject * asmine = dynamic_cast<ccMyBaseObject * >(child);

    if (asmine)
        this->getSPCElement()->addChild(asmine->getSPCElement());
}

void ccMyBaseObject::removeChild(int pos)
{
    DLOG(INFO) << "removing child by pos";

    ccMyBaseObject * asmine = dynamic_cast<ccMyBaseObject * >(m_children[pos]);

    if(asmine)
        this->getSPCElement()->removeChild(asmine->getSPCElement());

    ccHObject::removeChild(pos);
}

void ccMyBaseObject::setParent(ccHObject *parent)
{

    DLOG(INFO) << "set parent";
    ccHObject::setParent(parent);

    ccMyBaseObject * asmine = dynamic_cast<ccMyBaseObject * >(parent);
    if(asmine)
    {
        this->getSPCElement()->setParent(asmine->getSPCElement());

        if (this->getSPCElement()->isA(&spc::StratigraphicPositionableElement::Type))
        {
            if( asmine->getSPCElement()->isA(&spc::StratigraphicModelBase::Type))
            {
                spc::StratigraphicPositionableElement::Ptr positionable = spcDynamicPointerCast<spc::StratigraphicPositionableElement>(this->getSPCElement());
                if (positionable->getManual())
                {
                        positionable->modelFromParent();
                }
            }

        }

    }
    else
    {
        spc::StratigraphicPositionableElement::Ptr positionable = spcDynamicPointerCast<spc::StratigraphicPositionableElement>(this->getSPCElement());
        if (positionable!=NULL)
            positionable->setStratigraphicModel(NULL);
    }



}

void ccMyBaseObject::detachChild(ccHObject *child)
{
    DLOG(INFO) << "detached chaild";

    ccHObject::detachChild(child);

    ccMyBaseObject * asmine = dynamic_cast<ccMyBaseObject * >(child);

    if(asmine)
        this->getSPCElement()->removeChild(asmine->getSPCElement());
}

void ccMyBaseObject::setName(const QString &name)
{
    ccObject::setName(name);
    this->getSPCElement()->setElementName(name.toStdString());

}

void ccMyBaseObject::removeChild(ccHObject *child)
{
    DLOG(INFO) << "removing child by pointer";
    ccHObject::removeChild(child);


    ccMyBaseObject * asmine = dynamic_cast<ccMyBaseObject * >(child);


    if(asmine)
        this->getSPCElement()->removeChild(asmine->getSPCElement());
}
