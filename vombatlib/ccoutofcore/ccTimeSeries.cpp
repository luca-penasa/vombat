#include "ccTimeSeries.h"
#include <QIcon>
#include <spc/elements/TimeSeriesBase.h>

ccTimeSeries::ccTimeSeries(spc::TimeSeriesBase::Ptr series, const QString name): ccSPCElementShell(series, name)
{
//    series_ = series;
}

