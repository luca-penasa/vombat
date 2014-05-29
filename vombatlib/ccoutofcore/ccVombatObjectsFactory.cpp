#include "ccVombatObjectsFactory.h"
#include <ccSingleAttitudeModel.h>
#include <ccDynamicScalarFieldGenerator.h>
#include <ccSingleAttitudeModel.h>

ccVombatObjectsFactory::ccVombatObjectsFactory(QString name): ccExternalFactory(name)
{
}

ccHObject *ccVombatObjectsFactory::buildObject(const QString metaname)
{
    if (metaname == "ccAttitude")
        return new ccAttitude();

    else if (metaname == "ccSingleAttitudeModel")
        return new ccSingleAttitudeModel();

    else if (metaname == "ccDynamicScalarFieldGenerator")
        return new ccDynamicScalarFieldGenerator();

    else if (metaname == "ccSingleAttitudeModel")
        return new ccSingleAttitudeModel();

}
