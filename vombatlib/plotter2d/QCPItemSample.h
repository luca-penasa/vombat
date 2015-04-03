#ifndef QCPITEMSAMPLE_H
#define QCPITEMSAMPLE_H

#include <variantmanager.h>

#include <qcustomplot.h>
class ccSample;

//! a sample is a streight line, vertical
class QCPItemSample: public QCPItemStraightLine
{

	Q_OBJECT

	Q_PROPERTY(QPointF point READ point WRITE setPoint)
public:
	QCPItemSample(ccSample * sample, QCustomPlot *parentPlot);

	~QCPItemSample();

	void updateFromSample();

	QCPItemText * getLabel() const;


	void setPoint(const QPointF &p)
	{
		m_point = p;
	}

	QPointF point() const
	{
		return m_point;
	}

protected:
	ccSample * sample_;

	QCPItemText * text_;


	QPointF m_point;




	// QCPLayerable interface
	virtual void draw(QCPPainter *painter);
};

#endif // QCPITEMSAMPLE_H
