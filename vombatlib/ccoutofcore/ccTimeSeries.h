#ifndef CCTIMESERIES_H
#define CCTIMESERIES_H
#include "ccMyBaseObject.h"



class QIcon;

#include <spc/elements/TimeSeriesBase.h>


///
/// \brief The ccTimeSeries class contains any kind of spc-based time-series
///
class ccTimeSeries:  public ccMyBaseObject
{
public:

    ccTimeSeries(spc::TimeSeriesBase<float>::Ptr series);


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
};

#endif // CCTIMESERIES_H
