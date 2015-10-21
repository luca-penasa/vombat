#include "ccVombatObjectsFactory.h"
#include <ccSingleAttitudeModel.h>
#include <ccDynamicScalarFieldGenerator.h>
#include <ccSingleAttitudeModel.h>
#include <ccSample.h>
#include <ccTimeSeries.h>
#include <ccEigenTable.h>

ccVombatObjectsFactory::ccVombatObjectsFactory(QString name): ccExternalFactory(name)
{
}

ccHObject *ccVombatObjectsFactory::buildObject(const QString &metaname)
{



    if (metaname == "Attitude")
    {
        LOG(INFO) << " creating new ccAttitude!";
        return new ccAttitude();
        LOG(INFO) << " Done!";
    }

    if (metaname == "ElementBase")
    {
        LOG(INFO) << "trying to deserialize a pure elementbase";
        return 0;
    }

    else if (metaname == "SingleAttitudeModel")
        return new ccSingleAttitudeModel();

    else if (metaname == "DynamicScalarFieldGenerator")
        return new ccDynamicScalarFieldGenerator();

    else if (metaname == "Sample")
        return new ccSample();

    else if (metaname == "TimeSeries")
        return new ccTimeSeries();

    else if (metaname == "EigenTable")
        return new ccEigenTable();

    else
        return 0;

}
