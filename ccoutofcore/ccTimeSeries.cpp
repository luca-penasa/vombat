#include "ccTimeSeries.h"
#include <QIcon>
#include <spc/time_series/base_time_series.h>


ccTimeSeries::ccTimeSeries(spc::GenericTimeSeries<float>::Ptr series)
{
    initMetaData();
    series_ = series;
}

void ccTimeSeries::initMetaData()
{
    QVariant var(QString("Is a time Series"));
    setMetaData(QString("[vombat][ccTimeSeries]"), var);
}
