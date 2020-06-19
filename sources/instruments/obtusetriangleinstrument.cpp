#include "obtusetriangleinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"
#include "../dialogs/diagramnamedialog.h"
#include "../dialogs/numberdialog.h"

#include <QPen>
#include <QPainter>
#include <QtCore/qmath.h>

ObtuseTriangleInstrument::ObtuseTriangleInstrument(QObject *parent) :
	AbstractInstrument(parent)
{
	mPointsCount = 0;
	mAngle = 91;
}

void ObtuseTriangleInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
	{
		if (DataSingleton::Instance()->isResetCurve())
		{
			mPointsCount = 0;
			DataSingleton::Instance()->setResetCurve(false);
		}
		switch (mPointsCount)
		{
		case 0:
			mImageCopy = *imageArea.getImage();
			mStartPoint = mEndPoint = mFirstControlPoint = mLastDrawn = event->pos();
			++mPointsCount;
			mAngle = 91;
			mText = "";
			break;
		case 1:
			mFirstControlPoint = event->pos();
			mPointsCount = 0;
			break;
		}
		imageArea.setIsPaint(true);
		makeUndoCommand(imageArea);
	}
}

void ObtuseTriangleInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (imageArea.isPaint())
	{
		switch (mPointsCount)
		{
		case 1:
			mEndPoint = event->pos();
			break;
		case 0:
			mFirstControlPoint = event->pos();
			break;
		}

		imageArea.setImage(mImageCopy);
		if (event->buttons() & Qt::LeftButton)
			paint(imageArea, false);
		else if (event->buttons() & Qt::RightButton)
			paint(imageArea, true);
	}
}

void ObtuseTriangleInstrument::updateText(ImageArea *imageArea, QString textString)
{
	mText = textString;
	imageArea->setImage(mImageCopy);
	paint(*imageArea);

}

void ObtuseTriangleInstrument::updateAngle(ImageArea *imageArea, int angle)
{
	mAngle = angle;
	imageArea->setImage(mImageCopy);
	paint(*imageArea);

}

void ObtuseTriangleInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (imageArea.isPaint())
	{
		imageArea.setImage(mImageCopy);

		if (mPointsCount == 0) {
			DiagramNameDialog *td = new DiagramNameDialog(mText, &imageArea);
			connect(td, SIGNAL(textChanged(ImageArea *, QString)), this, SLOT(updateText(ImageArea *, QString)));
			connect(this, SIGNAL(sendCloseTextDialog()), td, SLOT(accept()));
			td->setAttribute(Qt::WA_DeleteOnClose);
			td->show();
		}
		else if(mPointsCount==1) {
			NumberDialog *td = new NumberDialog(mText, &imageArea, "Angle");
			connect(td, SIGNAL(valueChanged(ImageArea *, int)), this, SLOT(updateAngle(ImageArea *, int)));
			connect(this, SIGNAL(sendCloseTextDialog()), td, SLOT(accept()));
			td->setAttribute(Qt::WA_DeleteOnClose);
			td->show();
		}

		if (event->button() == Qt::LeftButton)
			paint(imageArea, false);
		else if (event->button() == Qt::RightButton)
			paint(imageArea, true);
		imageArea.setIsPaint(false);

	}
}

void ObtuseTriangleInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
	QPainter painter(imageArea.getImage());
	//choose color
	painter.setPen(QPen(isSecondaryColor ? DataSingleton::Instance()->getSecondaryColor() :
		DataSingleton::Instance()->getPrimaryColor(),
		DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
		Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	

	float midX = (float)(mStartPoint.rx() + mEndPoint.rx()) / 2;
	float midY = (float)(mStartPoint.ry() + mEndPoint.ry()) / 2;
	int minX = std::min({ mStartPoint.rx(), mEndPoint.rx(), mLastDrawn.rx() });
	int maxX = std::max({ mStartPoint.rx(), mEndPoint.rx(), mLastDrawn.rx() });
	int minY = std::min({ mStartPoint.ry(), mEndPoint.ry(), mLastDrawn.ry() });
	int maxY = std::max({ mStartPoint.ry(), mEndPoint.ry(), mLastDrawn.ry() });

	int font_size;
	QRect current_rect = QRect(QPoint(minX, minY), QPoint(maxX, maxY));
	for (font_size = 60; font_size > 2; font_size--) {
		QFontMetrics fm(QFont("Arial", font_size));
		QRect new_rect = fm.boundingRect(mText);
		if (new_rect.height() < current_rect.height() && new_rect.width() < current_rect.width())
			break;
	}

	float semiDist = qSqrt(qPow(midX - mFirstControlPoint.rx(), 2) + qPow(midY - mFirstControlPoint.ry(), 2));
	float radius = qSqrt(qPow(midX - mStartPoint.rx(), 2) + qPow(midY - mStartPoint.ry(), 2));

	painter.setFont(QFont("Arial", font_size - 2));

	float x1 = mStartPoint.x(), x2 = mEndPoint.x(), x3 = mStartPoint.x();
	float y1 = -1*mStartPoint.y(), y2 = -1*mEndPoint.y(), y3 = -1*mFirstControlPoint.y();
	//int theta =((x3 - x1)*(x2 - x1) + (y3 - y1)*(y2 - y1)) / (qSqrt(qPow(x3 - x1, 2) + qPow(y3 - y1, 2)) * qSqrt(qPow(x2 - x1, 2) + qPow(y2 - y1, 2)));
	int theta = (qAtan((y2 - y1)/(x2 - x1))- qAtan((y3 - y1) / (x3 - x1)))*180/(M_PI);
	
	if (mStartPoint.y() < mEndPoint.y()) {
		mFirstControlPoint.rx() = mStartPoint.x() - (mFirstControlPoint.y() - mStartPoint.y()) / qTan((float)(90 - mAngle + theta)*M_PI / 180);
		if (mFirstControlPoint.y() < mStartPoint.y()) {
			mFirstControlPoint.rx() = mStartPoint.x() - (mFirstControlPoint.y() - mStartPoint.y()) / qTan((float)(mAngle + theta - 90)*M_PI / 180);
		}
	}
	else {
		mFirstControlPoint.rx() = mStartPoint.x() - (mFirstControlPoint.y() - mStartPoint.y()) / qTan((float)(90 + mAngle - theta)*M_PI / 180);
		if (mFirstControlPoint.y() < mStartPoint.y()) {
			mFirstControlPoint.rx() = mStartPoint.x() - (mFirstControlPoint.y() - mStartPoint.y()) / qTan((float)(180-mAngle - theta + 90)*M_PI / 180);
		}
	}
	painter.drawPolygon(QPolygon(QVector<QPoint>({ mStartPoint, mFirstControlPoint, mEndPoint })));
	painter.drawText(QRect(QPoint(minX, minY), QPoint(maxX, maxY)), Qt::AlignCenter, mText);

	painter.end();
	imageArea.setEdited(true);
	imageArea.update();
}
