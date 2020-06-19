#include "convexpentagonselectioninstrument.h"
#include "../imagearea.h"
#include "../undocommand.h"
#include "math.h"

#include <QPainter>
#include <QApplication>
#include <QClipboard>

ConvexPentagonSelectionInstrument::ConvexPentagonSelectionInstrument(QObject *parent) :
	AbstractSelection(parent)
{
}

void ConvexPentagonSelectionInstrument::copyImage(ImageArea &imageArea)
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

void ConvexPentagonSelectionInstrument::cutImage(ImageArea &imageArea)
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

void ConvexPentagonSelectionInstrument::pasteImage(ImageArea &imageArea)
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

void ConvexPentagonSelectionInstrument::startAdjusting(ImageArea &imageArea)
{
	mImageCopy = *imageArea.getImage();
	mIsImageSelected = false;
}

void ConvexPentagonSelectionInstrument::startSelection(ImageArea &)
{
}

void ConvexPentagonSelectionInstrument::startResizing(ImageArea &imageArea)
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

void ConvexPentagonSelectionInstrument::startMoving(ImageArea &imageArea)
{
	clearSelectionBackground(imageArea);
	if (mIsSelectionAdjusting)
	{
		mIsImageSelected = false;
	}
}

void ConvexPentagonSelectionInstrument::select(ImageArea &)
{
}

void ConvexPentagonSelectionInstrument::resize(ImageArea &)
{
}

void ConvexPentagonSelectionInstrument::move(ImageArea &)
{
}

void ConvexPentagonSelectionInstrument::completeSelection(ImageArea &imageArea)
{
	mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
		mTopLeftPoint.y(),
		mWidth, mHeight);
	emit sendEnableCopyCutActions(true);
}

void ConvexPentagonSelectionInstrument::completeResizing(ImageArea &imageArea)
{
	mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
		mTopLeftPoint.y(),
		mWidth, mHeight);
}

void ConvexPentagonSelectionInstrument::completeMoving(ImageArea &imageArea)
{
	if (mIsSelectionAdjusting)
	{
		mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
			mTopLeftPoint.y(),
			mWidth, mHeight);
	}

}

void ConvexPentagonSelectionInstrument::clearSelectionBackground(ImageArea &imageArea)
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

void ConvexPentagonSelectionInstrument::clear()
{
	mSelectedImage = QImage();
	emit sendEnableCopyCutActions(false);
}

//ADDED IN PAINT FUNCTION
void ConvexPentagonSelectionInstrument::paint(ImageArea &imageArea, bool, bool)
{
	if (mIsSelectionExists && !mIsSelectionAdjusting)
	{
		if (mTopLeftPoint != mBottomRightPoint)
		{
			QPainter painter(imageArea.getImage());

			//ADDED IN THE PENTAGON REGION FOR THE BORDER 
			int xSize = mBottomRightPoint.x() - mTopLeftPoint.x();
			int ySize = mBottomRightPoint.y() - mTopLeftPoint.y();


			QPolygon pent;

			if (xSize > 0 && ySize > 0)
			{
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() - ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				pent << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
			}
			else if (xSize > 0 && ySize < 0)
			{
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				pent << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() - ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
			}
			else if (xSize < 0 && ySize < 0)
			{
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				pent << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() - ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
			}
			else
			{
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() - ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				pent << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
			}

			painter.setClipRegion(QRegion(pent));


			//Here we have our source and target variable which are on the imageArea. Couldn't figure
			//out how to incorporate these with QPolygon, so I had to leave as rectangles unfortunetly. 
			QRect source(0, 0, mSelectedImage.width(), mSelectedImage.height());
			QRect target(QPoint(mTopLeftPoint.x()-xSize,mTopLeftPoint.y()),QPoint(mTopLeftPoint.x()+xSize,mTopLeftPoint.y()+(ySize*2)));


			painter.drawImage(target, mSelectedImage, source);
			painter.end();
		}
		imageArea.setEdited(true);
		imageArea.update();
	}
}

//IMPLEMENTATION IF DRAW BORDER FOR CONVEX PENTAGON SHAPE
void ConvexPentagonSelectionInstrument::drawBorder(ImageArea &imageArea)
{
	if (mWidth > 1 && mHeight > 1)
	{
		QPainter painter(imageArea.getImage());
		painter.setPen(QPen(Qt::blue, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
		painter.setBackgroundMode(Qt::TransparentMode);
		if (mTopLeftPoint != mBottomRightPoint)
		{

			//ADDED IN THE PENTAGON REGION FOR THE BORDER 
			int xSize = mBottomRightPoint.x() - mTopLeftPoint.x();
			int ySize = mBottomRightPoint.y() - mTopLeftPoint.y();


			QPolygon pent;

			if (xSize > 0 && ySize > 0)
			{
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y()-ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				pent << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
			}
			else if (xSize > 0 && ySize < 0)
			{
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				pent << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() - ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
			}
			else if (xSize < 0 && ySize < 0)
			{
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				pent << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() - ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
			}
			else
			{
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() - ySize);
				pent << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				pent << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() + ySize);
				pent << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
			}
			painter.drawPolygon(pent);

			// painter.drawRect(QRect(mTopLeftPoint, mBottomRightPoint - QPoint(1, 1)));
		}
		imageArea.setEdited(true);
		painter.end();
		imageArea.update();
	}
}

void ConvexPentagonSelectionInstrument::showMenu(ImageArea &)
{
}
