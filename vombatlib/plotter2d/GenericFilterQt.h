#ifndef GENERICFILTERQT_H
#define GENERICFILTERQT_H


#include <QObject>
#include <spc/methods/GenericFilter.h>

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

#endif // GENERICFILTERQT_H
