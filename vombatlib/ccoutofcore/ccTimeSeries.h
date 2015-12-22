#pragma once
#ifndef CCTIMESERIES_H
#define CCTIMESERIES_H
#include "ccSPCElementShell.h"
#include <spc/core/spc_eigen.h>
//class QIcon;

namespace spc {
spcFwdDeclSharedPtr(TimeSeriesBase)
}


///
/// \brief The ccTimeSeries class contains any kind of spc-based time-series
///
class ccTimeSeries : public ccSPCElementShell
{
public:
    ccTimeSeries(spc::TimeSeriesBasePtr series, const QString name = QString(""));

    ccTimeSeries(): ccSPCElementShell(nullptr)
    {

    }

    virtual QIcon getIcon() const;

    spc::TimeSeriesBasePtr getTimeSeries() const;

    QVector<double> getX(const bool only_finite=false) const;

    QVector<double> getY(const bool only_finite=false) const;



};

#endif // CCTIMESERIES_H
