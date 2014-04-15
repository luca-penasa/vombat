#ifndef VOMBAT_MAINSCALE_H
#define VOMBAT_MAINSCALE_H

#include "qcustomplot.h"

//// every plot will be conncted witht this main scale
class MainScale: public QCPAxisRect
{
    Q_OBJECT
public:   
    MainScale(QCustomPlot *parentPlot);

    ~MainScale()
    {
        delete m_main_axis;
    }

    QCPAxis * getMainAxis() const;


protected:
    QCPAxis * m_main_axis;
//    QCPAxis * m_bottom_axis;
};

#endif // VOMBAT_MAINSCALE_H
