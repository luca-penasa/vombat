#include "ccVombatObjectsFactory.h"
#include <ccSingleAttitudeModel.h>
#include <ccDynamicScalarFieldGenerator.h>
#include <ccSingleAttitudeModel.h>
#include <ccSample.h>
#include <ccTimeSeries.h>
#include <ccCalibrationDB.h>

ccVombatObjectsFactory::ccVombatObjectsFactory(QString name): ccExternalFactory(name)
{
}

ccHObject *ccVombatObjectsFactory::buildObject(const QString &metaname)
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

    else if (metaname == "ccCalibrationDB")
        return new ccCalibrationDB();

    else
        return 0;

}
