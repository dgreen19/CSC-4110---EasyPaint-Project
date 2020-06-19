#include "scalenetriangularselectioninstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"
#include "../dialogs/diagramnamedialog.h"
#include "../undocommand.h"
#include "math.h"

#include <QPainter>
#include <QApplication>
#include <QClipboard>

ScaleneTriangularSelectionInstrument::ScaleneTriangularSelectionInstrument(QObject *parent) :
	AbstractSelection(parent)
{
	mPointsCount = 0;
}

void ScaleneTriangularSelectionInstrument::copyImage(ImageArea &imageArea)
{
	if (mIsSelectionExists)
	{
		imageArea.setImage(mImageCopy);
		QClipboard *globalClipboard = QApplication::clipboard();
		QImage copyImage;
		if (mIsImageSelected)
		{
			copyImage = mSelectedImage;
		}
		else
		{
			copyImage = imageArea.getImage()->copy(mTopLeftPoint.x(), mTopLeftPoint.y(), mWidth, mHeight);
		}
		globalClipboard->setImage(copyImage, QClipboard::Clipboard);
	}
}

void ScaleneTriangularSelectionInstrument::cutImage(ImageArea &imageArea)
{
	if (mIsSelectionExists)
	{
		copyImage(imageArea);
		if (mIsSelectionExists)
		{
			imageArea.setImage(mImageCopy);
			paint(imageArea);
		}
		makeUndoCommand(imageArea);
		if (/*mSelectedImage != mPasteImage || !*/mIsImageSelected)
		{
			imageArea.setImage(mImageCopy);
		}
		else
		{
			clearSelectionBackground(imageArea);
		}
		mTopLeftPoint = QPoint(0, 0);
		mBottomRightPoint = QPoint(0, 0);
		mImageCopy = *imageArea.getImage();
		imageArea.update();
		mIsSelectionExists = false;
		imageArea.restoreCursor();
		emit sendEnableCopyCutActions(false);
	}
}

void ScaleneTriangularSelectionInstrument::pasteImage(ImageArea &imageArea)
{
	QClipboard *globalClipboard = QApplication::clipboard();
	if (mIsSelectionExists)
	{
		imageArea.setImage(mImageCopy);
		paint(imageArea);
		mImageCopy = *imageArea.getImage();
	}
	makeUndoCommand(imageArea);
	mPasteImage = globalClipboard->image();
	if (!mPasteImage.isNull())
	{
		mSelectedImage = mPasteImage;
		mImageCopy = *imageArea.getImage();
		mTopLeftPoint = QPoint(0, 0);
		mBottomRightPoint = QPoint(mPasteImage.width(), mPasteImage.height()) - QPoint(1, 1);
		mHeight = mPasteImage.height();
		mWidth = mPasteImage.width();
		mIsImageSelected = mIsSelectionExists = true;
		paint(imageArea);
		drawBorder(imageArea);
		imageArea.restoreCursor();
		emit sendEnableCopyCutActions(true);
	}
}

void ScaleneTriangularSelectionInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
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

void ScaleneTriangularSelectionInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
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

void ScaleneTriangularSelectionInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
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



void ScaleneTriangularSelectionInstrument::startAdjusting(ImageArea &imageArea)
{
	mImageCopy = *imageArea.getImage();
	mIsImageSelected = false;
}

void ScaleneTriangularSelectionInstrument::startSelection(ImageArea &)
{
}

void ScaleneTriangularSelectionInstrument::startResizing(ImageArea &imageArea)
{
	if (!mIsImageSelected)
	{
		clearSelectionBackground(imageArea);
	}
	if (mIsSelectionAdjusting)
	{
		mIsImageSelected = false;
	}
}

void ScaleneTriangularSelectionInstrument::startMoving(ImageArea &imageArea)
{
	clearSelectionBackground(imageArea);
	if (mIsSelectionAdjusting)
	{
		mIsImageSelected = false;
	}
}

void ScaleneTriangularSelectionInstrument::select(ImageArea &)
{
}

void ScaleneTriangularSelectionInstrument::resize(ImageArea &)
{
}

void ScaleneTriangularSelectionInstrument::move(ImageArea &)
{
}

void ScaleneTriangularSelectionInstrument::completeSelection(ImageArea &imageArea)
{
	mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
		mTopLeftPoint.y(),
		mWidth, mHeight);
	emit sendEnableCopyCutActions(true);
}

void ScaleneTriangularSelectionInstrument::completeResizing(ImageArea &imageArea)
{
	mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
		mTopLeftPoint.y(),
		mWidth, mHeight);
}

void ScaleneTriangularSelectionInstrument::completeMoving(ImageArea &imageArea)
{
	if (mIsSelectionAdjusting)
	{
		mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
			mTopLeftPoint.y(),
			mWidth, mHeight);
	}

}

void ScaleneTriangularSelectionInstrument::clearSelectionBackground(ImageArea &imageArea)
{
	if (!mIsSelectionAdjusting)
	{
		QPainter blankPainter(imageArea.getImage());
		blankPainter.setPen(Qt::white);
		blankPainter.setBrush(QBrush(Qt::white));
		blankPainter.setBackgroundMode(Qt::OpaqueMode);
		blankPainter.drawRect(QRect(mTopLeftPoint, mBottomRightPoint - QPoint(1, 1)));
		blankPainter.end();
		mImageCopy = *imageArea.getImage();
	}
}

void ScaleneTriangularSelectionInstrument::clear()
{
	mSelectedImage = QImage();
	emit sendEnableCopyCutActions(false);
}




void ScaleneTriangularSelectionInstrument::drawBorder(ImageArea &imageArea)
{
	QPainter painter(imageArea.getImage());
	//choose color
	painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
		DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
		Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	painter.drawPolygon(QPolygon(QVector<QPoint>({ mStartPoint, mFirstControlPoint, mEndPoint })));

	int minX = std::min({ mStartPoint.rx(), mFirstControlPoint.rx(), mEndPoint.rx() });
	int maxX = std::max({ mStartPoint.rx(), mFirstControlPoint.rx(), mEndPoint.rx() });
	int minY = std::min({ mStartPoint.ry(), mFirstControlPoint.ry(), mEndPoint.ry() });
	int maxY = std::max({ mStartPoint.ry(), mFirstControlPoint.ry(), mEndPoint.ry() });

	int font_size;
	QRect current_rect = QRect(QPoint(minX, minY), QPoint(maxX, maxY));
	for (font_size = 60; font_size > 2; font_size--) {
		QFontMetrics fm(QFont("Arial", font_size));
		QRect new_rect = fm.boundingRect(mText);
		if (new_rect.height() < current_rect.height() && new_rect.width() < current_rect.width())
			break;
	}

	painter.setFont(QFont("Arial", font_size - 2));

	painter.drawText(QRect(QPoint(minX, minY), QPoint(maxX, maxY)), Qt::AlignCenter, mText);

	painter.end();
	imageArea.setEdited(true);
	imageArea.update();
}


void ScaleneTriangularSelectionInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
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
	int minY = std::min({ mStartPoint.ry(), mFirstControlPoint.ry(), mEndPoint.ry() });
	int maxY = std::max({ mStartPoint.ry(), mFirstControlPoint.ry(), mEndPoint.ry() });

	int font_size;
	QRect current_rect = QRect(QPoint(minX, minY), QPoint(maxX, maxY));
	for (font_size = 60; font_size > 2; font_size--) {
		QFontMetrics fm(QFont("Arial", font_size));
		QRect new_rect = fm.boundingRect(mText);
		if (new_rect.height() < current_rect.height() && new_rect.width() < current_rect.width())
			break;
	}

	painter.setFont(QFont("Arial", font_size - 2));

	painter.drawText(QRect(QPoint(minX, minY), QPoint(maxX, maxY)), Qt::AlignCenter, mText);

	painter.end();
	imageArea.setEdited(true);
	imageArea.update();
}

void ScaleneTriangularSelectionInstrument::showMenu(ImageArea &)
{
}