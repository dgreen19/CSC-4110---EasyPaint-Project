//ADDED BY DARRYL GREEN FOR CONVEX HEXAGON SELECTION INSTRUMENT
#include "convexhexagonselectioninstrument.h"
#include "../imagearea.h"
#include "../undocommand.h"
#include "math.h"

#include <QPainter>
#include <QApplication>
#include <QClipboard>

ConvexHexagonSelectionInstrument::ConvexHexagonSelectionInstrument(QObject *parent) :
	AbstractSelection(parent)
{
}

void ConvexHexagonSelectionInstrument::copyImage(ImageArea &imageArea)
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

void ConvexHexagonSelectionInstrument::cutImage(ImageArea &imageArea)
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

void ConvexHexagonSelectionInstrument::pasteImage(ImageArea &imageArea)
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

void ConvexHexagonSelectionInstrument::startAdjusting(ImageArea &imageArea)
{
	mImageCopy = *imageArea.getImage();
	mIsImageSelected = false;
}

void ConvexHexagonSelectionInstrument::startSelection(ImageArea &)
{
}

void ConvexHexagonSelectionInstrument::startResizing(ImageArea &imageArea)
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

void ConvexHexagonSelectionInstrument::startMoving(ImageArea &imageArea)
{
	clearSelectionBackground(imageArea);
	if (mIsSelectionAdjusting)
	{
		mIsImageSelected = false;
	}
}

void ConvexHexagonSelectionInstrument::select(ImageArea &)
{
}

void ConvexHexagonSelectionInstrument::resize(ImageArea &)
{
}

void ConvexHexagonSelectionInstrument::move(ImageArea &)
{
}

void ConvexHexagonSelectionInstrument::completeSelection(ImageArea &imageArea)
{
	mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
		mTopLeftPoint.y(),
		mWidth, mHeight);
	emit sendEnableCopyCutActions(true);
}

void ConvexHexagonSelectionInstrument::completeResizing(ImageArea &imageArea)
{
	mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
		mTopLeftPoint.y(),
		mWidth, mHeight);
}

void ConvexHexagonSelectionInstrument::completeMoving(ImageArea &imageArea)
{
	if (mIsSelectionAdjusting)
	{
		mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
			mTopLeftPoint.y(),
			mWidth, mHeight);
	}

}

void ConvexHexagonSelectionInstrument::clearSelectionBackground(ImageArea &imageArea)
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

void ConvexHexagonSelectionInstrument::clear()
{
	mSelectedImage = QImage();
	emit sendEnableCopyCutActions(false);
}



//Draw boarder implementation for Convex Hexagon
void ConvexHexagonSelectionInstrument::drawBorder(ImageArea &imageArea)
{
	if (mWidth > 1 && mHeight > 1)
	{
		QPainter painter(imageArea.getImage());
		painter.setPen(QPen(Qt::black, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
		painter.setBackgroundMode(Qt::TransparentMode);
		if (mTopLeftPoint != mBottomRightPoint)
		{

			//Region for hexagon border 
			int xSize = mBottomRightPoint.x() - mTopLeftPoint.x();
			int ySize = mBottomRightPoint.y() - mTopLeftPoint.y();


			QPolygon hex;

			//If-else statements determing points for the size of hexagon
			//Need set of 6 because hexagon can be positive/negative on both X/Y-axis
			if (xSize > 0 && ySize > 0)
			{
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);
			}
			else if (xSize > 0 && ySize < 0)
			{
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
			}
			else if (xSize < 0 && ySize < 0)
			{
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
			}
			else
			{
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);
			}
			painter.drawPolygon(hex);

		}
		imageArea.setEdited(true);
		painter.end();
		imageArea.update();
	}
}

//Paint Function for Convex Hexagon Selection
void ConvexHexagonSelectionInstrument::paint(ImageArea &imageArea, bool, bool)
{
	if (mIsSelectionExists && !mIsSelectionAdjusting)
	{
		if (mTopLeftPoint != mBottomRightPoint)
		{
			QPainter painter(imageArea.getImage());

			//Region for hexagon border 
			int xSize = mBottomRightPoint.x() - mTopLeftPoint.x();
			int ySize = mBottomRightPoint.y() - mTopLeftPoint.y();


			QPolygon hex;
			
			//If-else statements determing points for the size of hexagon
			//Need set of 6 because hexagon can be positive/negative on both X/Y-axis
			if (xSize > 0 && ySize > 0)
			{
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);

			}
			else if (xSize > 0 && ySize < 0)
			{
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
			}
			else if (xSize < 0 && ySize < 0)
			{
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
			}
			else
			{
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y() - ySize);
				hex << QPoint(mTopLeftPoint.x() + xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y() + ySize);
				hex << QPoint(mTopLeftPoint.x() - xSize, mBottomRightPoint.y());
				hex << QPoint(mTopLeftPoint.x(), mBottomRightPoint.y() - ySize);
			}

			painter.setClipRegion(QRegion(hex));



			QRect source(0, 0, mSelectedImage.width(), mSelectedImage.height());
			QRect target(QPoint(mTopLeftPoint.x() - xSize, mTopLeftPoint.y()), QPoint(mTopLeftPoint.x() + xSize, mTopLeftPoint.y() + (ySize * 2)));


			painter.drawImage(target, mSelectedImage, source);
			painter.end();
		}
		imageArea.setEdited(true);
		imageArea.update();
	}
}

void ConvexHexagonSelectionInstrument::showMenu(ImageArea &)
{
}
