#ifndef CCTIMESERIES_H
#define CCTIMESERIES_H
#include "ccMyBaseObject.h"



class QIcon;

#include <spc/elements/TimeSeriesBase.h>
#include <helpers/ccSPCObjectsStreamer.h>

///
/// \brief The ccTimeSeries class contains any kind of spc-based time-series
///
class ccTimeSeries:  public ccMyBaseObject
{
public:

    ccTimeSeries(spc::TimeSeriesBase<float>::Ptr series);

    ccTimeSeries()
    {
        writeSPCClassNameToMetadata();
    }


    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/tseries.png"));
    }



    spc::TimeSeriesBase<float>::Ptr getTimeSeries() const
    {
        return series_;
    }


    QVector<double> getX() const
    {
         std::vector<float> x = getTimeSeries()->getX();
         QVector<double> x_d;

         for (int i = 0; i < x.size(); ++i)
             x_d.push_back(x.at(i));


         return x_d;
    }


    QVector<double> getY() const
    {
        std::vector<float> y = getTimeSeries()->getY();
        QVector<double> y_d;


        for (int i = 0; i < y.size(); ++i)
            y_d.push_back(y.at(i));



        return y_d;
    }


protected:

    spc::TimeSeriesBase<float>::Ptr series_;

public:

    virtual QString getSPCClassName() const
    {
        return "ccTimeSeries";
    }


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
        spc::ElementBase::Ptr el =ccSPCObjectsStreamer::ReadFromQFile(in);
        series_ = spcDynamicPointerCast<spc::TimeSeriesBase<float>>(el);
        return true;
    }
};

#endif // CCTIMESERIES_H
