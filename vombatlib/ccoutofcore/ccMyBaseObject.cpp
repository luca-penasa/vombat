#include "ccMyBaseObject.h"

ccMyBaseObject::ccMyBaseObject()
{
    setMetaData(QString("plugin_name"), QVariant(QString("vombat")));
}

ccMyBaseObject::ccMyBaseObject(QString name) : ccCustomHObject(name)
{
    setMetaData(QString("plugin_name"), QVariant(QString("vombat")));
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
