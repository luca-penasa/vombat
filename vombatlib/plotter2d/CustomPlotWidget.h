#ifndef VOMBAT_CUSTOMPLOTWIDGET_H
#define VOMBAT_CUSTOMPLOTWIDGET_H

#include <external/qcustomplot.h>


class QWidget;

//// main plot widget
class CustomPlotWidget : public QCustomPlot
{
    Q_OBJECT
public:
    explicit CustomPlotWidget(QWidget *parent = 0);

    ~CustomPlotWidget();
};


#endif // CUSTOMPLOTWIDGET_H
