#include "scalenetriangleinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"
#include "../dialogs/diagramnamedialog.h"

#include <QPen>
#include <QPainter>
#include <QtCore/qmath.h>


ScaleneTriangleInstrument::ScaleneTriangleInstrument(QObject *parent) :
	AbstractInstrument(parent)
{
	mPointsCount = 0;
}

void ScaleneTriangleInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
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
			mStartPoint = mEndPoint = mFirstControlPoint = event->pos();
			++mPointsCount;
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

void ScaleneTriangleInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
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

void ScaleneTriangleInstrument::updateText(ImageArea *imageArea, QString textString)
{
	mText = textString;
	imageArea->setImage(mImageCopy);
	paint(*imageArea);
	
}

void ScaleneTriangleInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
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

		if (event->button() == Qt::LeftButton)
			paint(imageArea, false);
		else if (event->button() == Qt::RightButton)
			paint(imageArea, true);
		imageArea.setIsPaint(false);
		
	}
}

void ScaleneTriangleInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
	QPainter painter(imageArea.getImage());
    //choose color
    painter.setPen(QPen(isSecondaryColor ? DataSingleton::Instance()->getSecondaryColor() :
                                           DataSingleton::Instance()->getPrimaryColor(),
                        DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	painter.drawPolygon(QPolygon(QVector<QPoint>({ mStartPoint, mFirstControlPoint, mEndPoint })));
	
	int minX = std::min({ mStartPoint.rx(), mFirstControlPoint.rx(), mEndPoint.rx() });
	int maxX = std::max({ mStartPoint.rx(), mFirstControlPoint.rx(), mEndPoint.rx() });
	int minY = std::min({mStartPoint.ry(), mFirstControlPoint.ry(), mEndPoint.ry()});
	int maxY = std::max({mStartPoint.ry(), mFirstControlPoint.ry(), mEndPoint.ry()});
	
	int font_size;
	QRect current_rect = QRect(QPoint(minX, minY), QPoint(maxX, maxY));
	for (font_size = 60; font_size > 2; font_size--) {
		QFontMetrics fm(QFont("Arial", font_size));
		QRect new_rect = fm.boundingRect(mText);
		if (new_rect.height() < current_rect.height() && new_rect.width() < current_rect.width())
			break;
	}

	painter.setFont(QFont("Arial", font_size-2));

	painter.drawText(QRect(QPoint(minX, minY), QPoint(maxX, maxY)), Qt::AlignCenter, mText);

	painter.end();
	imageArea.setEdited(true);
	imageArea.update();
}
