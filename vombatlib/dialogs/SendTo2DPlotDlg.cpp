#include "SendTo2DPlotDlg.h"
#include "ui_SendTo2DPlotDlg.h"

#include <vombat.h>

#include <qcustomplot.h>

SendTo2DPlotDlg::SendTo2DPlotDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendTo2DPlotDlg)
{

    ui->setupUi(this);

    QMetaObject meta = QCPGraph::staticMetaObject;
    int index = meta.indexOfEnumerator("LineStyle");

    QMetaEnum metaEnum = meta.enumerator(index);

    for (int i = 0 ; i < metaEnum.keyCount() ; ++i)
    {
        QString name  = metaEnum.valueToKey( i );
        ui->cmbLineStyle->addItem(name);

    }

    ui->cmbLineStyle->setCurrentIndex(1);

     meta = QCPScatterStyle::staticMetaObject;
     index = meta.indexOfEnumerator("ScatterShape");

     metaEnum = meta.enumerator(index);

    for (int i = 0 ; i < metaEnum.keyCount() ; ++i)
    {
        QString name  = metaEnum.valueToKey( i );
        ui->cmbScatterStyle->addItem(name);

    }
}

SendTo2DPlotDlg::~SendTo2DPlotDlg()
{
    delete ui;
}

QCPGraph::LineStyle SendTo2DPlotDlg::getLineStyle() const
{
    int selected = ui->cmbLineStyle->currentIndex();

    return (QCPGraph::LineStyle) selected;
}

QCPScatterStyle::ScatterShape SendTo2DPlotDlg::getScatterShape() const
{
    int selected = ui->cmbScatterStyle->currentIndex();

    return (QCPScatterStyle::ScatterShape) selected;
}


