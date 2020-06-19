#include "regularpentagoninstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"
#include <cmath>
#include "textinstrument.h"
#include "../dialogs/textdialog.h"

#include <QPen>
#include <QPainter>

RegularPentagonInstrument::RegularPentagonInstrument(QObject *parent) :
	AbstractInstrument(parent)
{

}
void RegularPentagonInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
	{
		mStartPoint = mEndPoint = event->pos();
		imageArea.setIsPaint(true);
		mImageCopy = *imageArea.getImage();
		makeUndoCommand(imageArea);
	}
}

void RegularPentagonInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (imageArea.isPaint())
	{
		mEndPoint = event->pos();
		imageArea.setImage(mImageCopy);
		if (event->buttons() & Qt::LeftButton)
		{
			paint(imageArea, false);
		}
		else if (event->buttons() & Qt::RightButton)
		{
			paint(imageArea, true);
		}
	}
}

void RegularPentagonInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (imageArea.isPaint())
	{
		imageArea.setImage(mImageCopy);
		if (event->button() == Qt::LeftButton)
		{
			
			
			paint(imageArea, false);

		}
		else if (event->button() == Qt::RightButton)
		{
			paint(imageArea, true);
		}
		
		imageArea.setIsPaint(false);
	}
}

void RegularPentagonInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool additionalFlag)
{
	QPainter painter(imageArea.getImage());
	painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
		DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
		Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	if (isSecondaryColor)
	{
		painter.setBrush(QBrush(DataSingleton::Instance()->getSecondaryColor()));
	}
	if (mStartPoint != mEndPoint)
	{

		//Added in functionality for a regular Pentagon
		QPolygon poly;

		int absXSize, absYSize, xSize, ySize;

		xSize = mStartPoint.x() - mEndPoint.x();
		ySize = mStartPoint.y() - mEndPoint.y();

		absXSize = abs(xSize);
		absYSize = abs(ySize);

		//If-else statements determing points for the size of the pentagon based on the starting position and ending position of the mouse.
		//Needed a set of 4 because the pentagon can be positive/negative in both the X and Y directions
		if (xSize > 0 && ySize > 0)
		{
			poly << QPoint(504.5, 100.0)*.5;
			poly << QPoint(100.0, 393.9)*.5;
			poly << QPoint(254.5, 869.4)*.5;
			poly << QPoint(754.5, 869.4)*.5;
			poly << QPoint(909.0, 393.9)*.5;
		}
			
	
		else if (xSize > 0 && ySize < 0)
		{
		
			poly << QPoint(504.5, 100.0)*.5;
			poly << QPoint(100.0, 393.9)*.5;
			poly << QPoint(254.5, 869.4)*.5;
			poly << QPoint(754.5, 869.4)*.5;
			poly << QPoint(909.0, 393.9)*.5;

		}
		else if (xSize < 0 && ySize < 0)
		{
		

			poly << QPoint(504.5, 100.0)*.5;
			poly << QPoint(100.0, 393.9)*.5;
			poly << QPoint(254.5, 869.4)*.5;
			poly << QPoint(754.5, 869.4)*.5;
			poly << QPoint(909.0, 393.9)*.5;
		}
		else
		{
			poly << QPoint(504.5, 100.0)*.5;
			poly << QPoint(100.0, 393.9)*.5;
			poly << QPoint(254.5, 869.4)*.5;
			poly << QPoint(754.5, 869.4)*.5;
			poly << QPoint(909.0, 393.9)*.5;

		}


		painter.drawPolygon(poly);
	}
	imageArea.setEdited(true);
	//    int rad(DataSingleton::Instance()->getPenSize() + round(sqrt((mStartPoint.x() - mEndPoint.x()) *
	//                                                                 (mStartPoint.x() - mEndPoint.x()) +
	//                                                                 (mStartPoint.y() - mEndPoint.y()) *
	//                                                                 (mStartPoint.y() - mEndPoint.y()))));
	//    mPImageArea->update(QRect(mStartPoint, mEndPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
	painter.end();
	imageArea.update();

}