#ifndef CCVOMBATOBJECTSFACTORY_H
#define CCVOMBATOBJECTSFACTORY_H

#include <QString>
#include "ccAttitude.h"

#include <ccExternalFactory.h>

class ccVombatObjectsFactory : public ccExternalFactory
{
public:

    ccVombatObjectsFactory(QString name) ;

    virtual ccHObject * buildObject(const QString &metaname);
};

#endif // CCVOMBATOBJECTSFACTORY_H
