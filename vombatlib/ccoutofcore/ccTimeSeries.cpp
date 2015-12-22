#include "ccTimeSeries.h"
#include <QIcon>
#include <spc/elements/TimeSeriesBase.h>
#include <helpers/ccSPCObjectsStreamer.h>
ccTimeSeries::ccTimeSeries(spc::TimeSeriesBase::Ptr series, const QString name): ccSPCElementShell(series, name)
{
//    series_ = series;
}


QIcon ccTimeSeries::getIcon() const
{
    return QIcon(QString::fromUtf8(":/toolbar/icons/time_series.png"));
}

QVector<double> ccTimeSeries::getX(const bool only_finite) const
{
    Eigen::VectorXf x = getTimeSeries()->getX();
    Eigen::VectorXf y = getTimeSeries()->getY();

    QVector<double> x_d;

    for (int i = 0; i < x.size(); ++i)
    {
        if (only_finite)
        {
            if (std::isfinite(y(i)) && std::isfinite(x(i)))
                x_d.push_back(x(i));
        }
        else
            x_d.push_back(x(i));
    }

    return x_d;
}

QVector<double> ccTimeSeries::getY(const bool only_finite) const
{
    Eigen::VectorXf y = getTimeSeries()->getY();
    Eigen::VectorXf x = getTimeSeries()->getX();


    QVector<double> y_d;

    for (int i = 0; i < y.size(); ++i)
    {
        if (only_finite)
        {
            if (std::isfinite(y(i)) && std::isfinite(x(i)))
                y_d.push_back(y(i));
        }
        else
            y_d.push_back(y(i));
    }

    return y_d;
}

spc::TimeSeriesBase::Ptr ccTimeSeries::getTimeSeries() const
{
    return this->getSPCElement<spc::TimeSeriesBase>();
}
