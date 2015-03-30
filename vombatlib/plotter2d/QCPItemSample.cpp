#include "QCPItemSample.h"

#include <ccoutofcore/ccSample.h>

QCPItemSample::QCPItemSample(ccSample *sample, QCustomPlot *parentPlot) : QCPItemStraightLine(parentPlot),
	sample_(sample)
{
	//lock the sample
	sample_->setLocked(true);

	text_ = new QCPItemText(parentPlot);

	updateFromSample();



}

QCPItemSample::~QCPItemSample()
{
	// unlock the sample
	sample_->setLocked(false);		
}

void QCPItemSample::updateFromSample()
{
	float sp = sample_->getSample()->getStratigraphicPosition();
	if (sp == spcNANMacro)
	{
		DLOG(WARNING) << "the sample does not have a valid stratigraphic position";
		this->setVisible(false);
	}
	else
	{
		this->setVisible(true);
		this->point1->setCoords(sp, 0.0);
		this->point2->setCoords(sp, 1.0);
	}

	// the text
	text_->setText(sample_->getName());
	text_->setRotation(90);
	text_->setPositionAlignment(Qt::AlignTop | Qt::AlignLeft);
	text_->position->setTypeY(QCPItemPosition::ptAbsolute);
	text_->position->setTypeX(QCPItemPosition::ptPlotCoords);
	text_->position->setCoords(sp, clipRect().top());
}

QCPItemText *QCPItemSample::getLabel() const
{
	return text_;
}

void QCPItemSample::draw(QCPPainter *painter)
{
	this->updateFromSample();

	QVector2D start(point1->pixelPoint());
	QVector2D end(point2->pixelPoint());
	// get visible segment of straight line inside clipRect:
	double clipPad = mainPen().widthF();
	QLineF line = getRectClippedStraightLine(start, end-start, clipRect().adjusted(-clipPad, -clipPad, clipPad, clipPad));
	// paint visible segment, if existent:
	if (!line.isNull())
	{
	  painter->setPen(mainPen());
	  painter->drawLine(line);
	}

}
