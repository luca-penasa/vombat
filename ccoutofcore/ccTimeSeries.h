#ifndef CCTIMESERIES_H
#define CCTIMESERIES_H
#include "ccMyBaseObject.h"



class QIcon;

#include <spc/time_series/base_time_series.h>


///
/// \brief The ccTimeSeries class contains any kind of spc-based time-series
///
class ccTimeSeries:  public ccMyBaseObject
{
public:

    ccTimeSeries(spc::GenericTimeSeries<float>::Ptr series);


    virtual QIcon * getIcon() const
    {
        return new QIcon(QString::fromUtf8(":/toolbar/icons/tseries.png"));
    }



    spc::GenericTimeSeries<float>::Ptr getTimeSeries() const
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
    void initMetaData();

    spc::GenericTimeSeries<float>::Ptr series_;
};

#endif // CCTIMESERIES_H
