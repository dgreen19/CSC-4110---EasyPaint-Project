#include "concavepentagonselectioninstrument.h"
#include "../imagearea.h"
#include "../undocommand.h"
#include "math.h"

#include <QPainter>
#include <QApplication>
#include <QClipboard>

ConcavePentagonSelectionInstrument::ConcavePentagonSelectionInstrument(QObject *parent) :
	AbstractSelection(parent)
{
}

void ConcavePentagonSelectionInstrument::copyImage(ImageArea &imageArea)
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

void ConcavePentagonSelectionInstrument::cutImage(ImageArea &imageArea)
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

void ConcavePentagonSelectionInstrument::pasteImage(ImageArea &imageArea)
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

void ConcavePentagonSelectionInstrument::startAdjusting(ImageArea &imageArea)
{
	mImageCopy = *imageArea.getImage();
	mIsImageSelected = false;
}

void ConcavePentagonSelectionInstrument::startSelection(ImageArea &)
{
}

void ConcavePentagonSelectionInstrument::startResizing(ImageArea &imageArea)
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

void ConcavePentagonSelectionInstrument::startMoving(ImageArea &imageArea)
{
	clearSelectionBackground(imageArea);
	if (mIsSelectionAdjusting)
	{
		mIsImageSelected = false;
	}
}

void ConcavePentagonSelectionInstrument::select(ImageArea &)
{
}

void ConcavePentagonSelectionInstrument::resize(ImageArea &)
{
}

void ConcavePentagonSelectionInstrument::move(ImageArea &)
{
}

void ConcavePentagonSelectionInstrument::completeSelection(ImageArea &imageArea)
{
	mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
		mTopLeftPoint.y(),
		mWidth, mHeight);
	emit sendEnableCopyCutActions(true);
}

void ConcavePentagonSelectionInstrument::completeResizing(ImageArea &imageArea)
{
	mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
		mTopLeftPoint.y(),
		mWidth, mHeight);
}

void ConcavePentagonSelectionInstrument::completeMoving(ImageArea &imageArea)
{
	if (mIsSelectionAdjusting)
	{
		mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
			mTopLeftPoint.y(),
			mWidth, mHeight);
	}

}

void ConcavePentagonSelectionInstrument::clearSelectionBackground(ImageArea &imageArea)
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

void ConcavePentagonSelectionInstrument::clear()
{
	mSelectedImage = QImage();
	emit sendEnableCopyCutActions(false);
}

void ConcavePentagonSelectionInstrument::paint(ImageArea &imageArea, bool, bool)
{
	if (mIsSelectionExists && !mIsSelectionAdjusting)
	{
		if (mTopLeftPoint != mBottomRightPoint)
		{
			QPainter painter(imageArea.getImage());
			QRect source(0, 0, mSelectedImage.width(), mSelectedImage.height());
			QRect target(mTopLeftPoint, mBottomRightPoint);
			painter.drawImage(target, mSelectedImage, source);
			painter.end();
		}
		imageArea.setEdited(true);
		imageArea.update();
	}
}

void ConcavePentagonSelectionInstrument::drawBorder(ImageArea & imageArea)
{
}

void ConcavePentagonSelectionInstrument::showMenu(ImageArea &)
{
}
