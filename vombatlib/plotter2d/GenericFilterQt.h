#ifndef GENERICFILTERQT_H
#define GENERICFILTERQT_H


#include <QObject>
#include <spc/methods/GenericFilter.h>
#include <spc/methods/TimeSeriesBandPassFilter.h>

class GenericFilterQt: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString FilterName READ getFilterName )

    Q_PROPERTY(bool Compute READ getCompute WRITE setCompute NOTIFY doCompute)


public:
    GenericFilterQt(spc::GenericFilter::Ptr filter, QObject * parent = nullptr);

    QString getFilterName() const;

signals:
    void activated(GenericFilterQt *);

    void doCompute();

public slots:
    void doComputations();

    void activate(bool toggle);

    bool canCompute();


    bool getCompute() const
    {
        return compute_;
    }

    void setCompute( const bool & status)
    {
        compute_ = true;
        emit doCompute();
    }


    void setCurrentSelection(const QList<QObject *> &objs)
    {
        current_selection = objs;
    }

protected:

    spc::GenericFilter::Ptr filter_;

    bool compute_ = false;

    QList<QObject * > current_selection;
};


class GFBandpass: public GenericFilterQt
{
    Q_OBJECT

    Q_PROPERTY(double LowFreq READ getLowFreq WRITE setLowFreq)

    Q_PROPERTY(double HighFreq READ getHighFreq WRITE setHighFreq)

        Q_PROPERTY(double LongPeriod READ getLongerPeriod WRITE setLongerPeriod)

        Q_PROPERTY(double ShortPeriod READ getShorterPeriod WRITE setShorterPeriod)
public:

     GFBandpass(spc::GenericFilter::Ptr filter, QObject * parent = nullptr): GenericFilterQt(filter, parent)
     {
     }


    spc::TimeSeriesBandPassFilter::Ptr getBandpassFilter() const;


    double getLowFreq() const;

    void setLowFreq(const double f);


    double getHighFreq() const;

    void setHighFreq(const double f);


    double getLongerPeriod() const
    {
        return 1/getLowFreq();
    }

    void setLongerPeriod (const double p)
    {
        setLowFreq(1/p);
    }

    double getShorterPeriod() const
    {
        return 1/getHighFreq();
    }

    void setShorterPeriod (const double p)
    {
        setHighFreq(1/p);
    }









};


#endif // GENERICFILTERQT_H
