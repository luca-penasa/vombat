#include "ccTimeSeries.h"
#include <QIcon>
#include <spc/elements/TimeSeriesBase.h>

ccTimeSeries::ccTimeSeries(spc::GenericTimeSeries<float>::Ptr series)
{
    series_ = series;

}

