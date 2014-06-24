#ifndef COMPOSER_H
#define COMPOSER_H

#include <QWidget>

#include <QDialog>

#include <qcustomplot.h>
namespace Ui {
class SendTo2DPlotDlg;
}



class SendTo2DPlotDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SendTo2DPlotDlg(QWidget *parent = 0);
    ~SendTo2DPlotDlg();

    QCPGraph::LineStyle getLineStyle() const;


    QCPScatterStyle::ScatterShape getScatterShape() const;
private:
    Ui::SendTo2DPlotDlg *ui;
};

#endif // COMPOSER_H
