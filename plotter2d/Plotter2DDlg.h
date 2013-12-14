//##########################################################################
//#                                                                        #
//#                            CLOUDCOMPARE                                #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#          COPYRIGHT: EDF R&D / TELECOM ParisTech (ENST-TSI)             #
//#                                                                        #
//##########################################################################



#ifndef VOMBAT_PLOTTER2D_HEADER
#define VOMBAT_PLOTTER2D_HEADER

#include <QDialog>



class QCPAxis;
class QCustomPlot;
class ccTimeSeries;

namespace Ui
{
    class Plotter2DDlgUi;
}

//// te dialog with the widgt collecting the plots
class Plotter2DDlg : public QDialog
{
    Q_OBJECT
public:
    Plotter2DDlg(QWidget *parent=0);

signals:
    ///every time a ts is plottet this will be emitted
    void seriesAdded(ccTimeSeries * series);

public slots:
    void addPlot(ccTimeSeries * series);




protected:

    virtual void dropEvent(QDropEvent *de);
    void dragMoveEvent(QDragMoveEvent *de);
    void dragEnterEvent(QDragEnterEvent *event);



    bool isYetPlotted(ccTimeSeries * ser);

    QCustomPlot * getPlotWidget() const;


    Ui::Plotter2DDlgUi * ui;

    std::vector<ccTimeSeries *> all_series_;


};









#endif

