#include "ccSPCElementShell.h"

#include <spc/elements/StratigraphicPositionableElement.h>
#include <spc/elements/GeometricElement3DBase.h>

//ccSPCElementShell::ccSPCElementShell()
//{

//    DLOG(INFO) << "created a ccSPCElementShell";

//}

//ccSPCElementShell::ccSPCElementShell(QString name) : ccCustomHObject(name)
//{
//    setMetaData(QString("plugin_name"), QVariant(QString("vombat")));
//    DLOG(INFO) << "created a ccSPCElementShell";
//}



void ccSPCElementShell::writeSPCClassNameToMetadata()
{
    QString name = this->getSPCClassName();
    setMetaData(QString("class_name"), QVariant(QString(name)));
    setMetaData(QString("plugin_name"), QVariant(QString("vombat")));

}


bool ccSPCElementShell::addChild(ccHObject *child, int dependencyFlags, int insertIndex)
{

    DLOG(INFO) << "adding child";

    ccHObject::addChild(child, dependencyFlags, insertIndex);

    ccSPCElementShell * asmine = dynamic_cast<ccSPCElementShell * >(child);

    if (asmine)
        this->getSPCElement()->addChild(asmine->getSPCElement());

	return true;
}

void ccSPCElementShell::removeChild(int pos)
{
    DLOG(INFO) << "removing child by pos";

    ccSPCElementShell * asmine = dynamic_cast<ccSPCElementShell * >(m_children[pos]);

    if(asmine)
        this->getSPCElement()->removeChild(asmine->getSPCElement());

    ccHObject::removeChild(pos);
}

void ccSPCElementShell::setParent(ccHObject *parent)
{

    DLOG(INFO) << "set parent";
    ccHObject::setParent(parent);

    ccSPCElementShell * asmine = dynamic_cast<ccSPCElementShell * >(parent);
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

void ccSPCElementShell::detachChild(ccHObject *child)
{
    DLOG(INFO) << "detached chaild";

    ccHObject::detachChild(child);

    ccSPCElementShell * asmine = dynamic_cast<ccSPCElementShell * >(child);

    if(asmine)
        this->getSPCElement()->removeChild(asmine->getSPCElement());
}

void ccSPCElementShell::setName(const QString &name)
{
    ccObject::setName(name);
    this->getSPCElement()->setElementName(name.toStdString());

}

void ccSPCElementShell::applyGLTransformation(const ccGLMatrix &trans)
{
    spc::ElementBase::Ptr elbase = this->getSPCElement();

    spc::GeometricElement3DBase::Ptr geom = std::dynamic_pointer_cast<spc::GeometricElement3DBase> (elbase);

    if (geom)
    {

        Eigen::Map<const Eigen::Matrix4f> mat (trans.data());
        spc::GeometricElement3DBase::TransformT t(mat);

        geom->applyTransform(t);
    }


    ccHObject::applyGLTransformation(trans);

}

void ccSPCElementShell::removeChild(ccHObject *child)
{
    DLOG(INFO) << "removing child by pointer";
    ccHObject::removeChild(child);


    ccSPCElementShell * asmine = dynamic_cast<ccSPCElementShell * >(child);


    if(asmine)
        this->getSPCElement()->removeChild(asmine->getSPCElement());
}
