#include "SinglePlot.h"
#include <iostream>

#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>

SinglePlot::SinglePlot(QCustomPlot *parentPlot): QCPAxisRect(parentPlot, false)
{
    init();

}

//SinglePlot::SinglePlot(QCustomPlot *parentPlot, spc::ContinousValuesLog *log): QCPAxisRect(parentPlot, false)
//{
//    init();
//    updateDataWith(log);
//}

//void SinglePlot::updateDataWith(const spc::ContinousValuesLog *log)
//{
//    //data are copied!
//    QVector<double> m_depth = QVector<double>::fromStdVector(log->getStratigraphicPositions<double>());
//    QVector<double> m_values = QVector<double>::fromStdVector(log->getValues<double>());

//    // set these data into the graph
//    updateGraphData( m_depth,m_values);



//}

void SinglePlot::updateDataWith(ccTimeSeries * tserie)
{
    std::vector<float> depth = tserie->getTimeSeries()->getX();
    std::vector<float> val = tserie->getTimeSeries()->getY();

    QVector<double> m_depth, m_values;

    spcForEachMacro( float  d, depth)
    {
        m_depth.append((double) d);
    }

    spcForEachMacro( float v, val)
    {

        m_values.append((double) v);
    }

    updateGraphData(m_depth, m_values);


    /// keep a pointer to this time series (until class is destructed)
    m_tseries = tserie;

}



void SinglePlot::init()
{
    setMaximumSize(QSize(250, 1000000000)); // we limit the size in width
    setMinimumSize(120, 120);
    m_bottom_axis = addAxis(QCPAxis::atBottom);
    m_bottom_axis->setTickLabelRotation(60);
    m_depth_axis = addAxis(QCPAxis::atLeft);

    m_depth_axis->setVisible(false);

    //create a graph
    m_graph = parentPlot()->addGraph(m_depth_axis, m_bottom_axis);

    this->setMargins(QMargins(0,0,0,0));


}
