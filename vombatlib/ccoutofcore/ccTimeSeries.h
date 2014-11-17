#ifndef CCTIMESERIES_H
#define CCTIMESERIES_H
#include "ccSPCElementShell.h"

class QIcon;

#include <spc/elements/TimeSeriesBase.h>
#include <helpers/ccSPCObjectsStreamer.h>

///
/// \brief The ccTimeSeries class contains any kind of spc-based time-series
///
class ccTimeSeries : public ccSPCElementShell
{
public:
    ccTimeSeries(spc::TimeSeriesBase::Ptr series, const QString name = QString(""));

    ccTimeSeries(): ccSPCElementShell(NULL)
    {

    }

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/time_series.png"));
    }

    spc::TimeSeriesBase::Ptr getTimeSeries() const
    {
        return series_;
    }

    QVector<double> getX(const bool only_finite=false) const
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

    QVector<double> getY(const bool only_finite=false) const
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

protected:
    spc::TimeSeriesBase::Ptr series_;

public:




    // ccHObject interface
protected:
    virtual bool toFile_MeOnly(QFile &out) const
    {
        ccCustomHObject::toFile_MeOnly(out);
        ccSPCObjectsStreamer::WriteToQFile(series_, out);
        return true;
    }
    virtual bool fromFile_MeOnly(QFile &in, short dataVersion, int flags)
    {
        ccCustomHObject::fromFile_MeOnly(in, dataVersion, flags);
        spc::ISerializable::Ptr el = ccSPCObjectsStreamer::ReadFromQFile(in);
        series_ = spcDynamicPointerCast<spc::TimeSeriesBase>(el);
        return true;
    }
};

#endif // CCTIMESERIES_H
