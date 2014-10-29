#ifndef CCVOMBATOBJECTSFACTORY_H
#define CCVOMBATOBJECTSFACTORY_H

#include <QString>
#include "ccAttitude.h"

#include <ccExternalFactory.h>

class ccVombatObjectsFactory : public ccExternalFactory
{
public:

    ccVombatObjectsFactory(QString name) : ccExternalFactory(name)
    {
    }

    virtual ccHObject * buildObject(const QString &metaname)
    {

        if (metaname == "ccAttitude")
            return new ccAttitude();

        else if (metaname == "ccSingleAttitudeModel")
            return new ccSingleAttitudeModel();

        else if (metaname == "ccDynamicScalarFieldGenerator")
            return new ccDynamicScalarFieldGenerator();

        else if (metaname == "ccSample")
            return new ccSample();

        else if (metaname == "ccTimeSeries")
            return new ccTimeSeries();

        else if (metaname == "ccEigenTable")
            return new ccEigenTable();

        else
            return 0;

    }
};

#endif // CCVOMBATOBJECTSFACTORY_H
