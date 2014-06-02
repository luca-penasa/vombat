#include "ccTimeSeries.h"
#include <QIcon>
#include <spc/elements/TimeSeriesBase.h>

ccTimeSeries::ccTimeSeries(spc::TimeSeriesBase<float>::Ptr series)
{
    series_ = series;
    writeSPCClassNameToMetadata();

}

