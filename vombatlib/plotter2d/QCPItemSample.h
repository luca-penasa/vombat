#ifndef QCPITEMSAMPLE_H
#define QCPITEMSAMPLE_H

#include <qcustomplot.h>
class ccSample;

//! a sample is a streight line, vertical
class QCPItemSample: public QCPItemStraightLine
{

	Q_OBJECT
public:
	QCPItemSample(ccSample * sample, QCustomPlot *parentPlot);

	~QCPItemSample();

	void updateFromSample();

	QCPItemText * getLabel() const;

protected:
	ccSample * sample_;

	QCPItemText * text_;

	// QCPLayerable interface
	virtual void draw(QCPPainter *painter);
};

#endif // QCPITEMSAMPLE_H
