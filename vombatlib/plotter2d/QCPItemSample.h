#ifndef QCPITEMSAMPLE_H
#define QCPITEMSAMPLE_H

#include <variantmanager.h>

#include <qcustomplot.h>
class ccSample;

//! a sample is a streight line, vertical
class QCPItemSample: public QCPItemStraightLine
{

	Q_OBJECT

	Q_PROPERTY(FilePathPropertyType path READ path WRITE setPath)
public:
	QCPItemSample(ccSample * sample, QCustomPlot *parentPlot);

	~QCPItemSample();

	void updateFromSample();

	QCPItemText * getLabel() const;


	void setPath(const FilePathPropertyType &path)
	{
		m_path = path;
	}

	FilePathPropertyType path() const
	{
		return m_path;
	}

protected:
	ccSample * sample_;

	QCPItemText * text_;


	FilePathPropertyType m_path;




	// QCPLayerable interface
	virtual void draw(QCPPainter *painter);
};

#endif // QCPITEMSAMPLE_H
