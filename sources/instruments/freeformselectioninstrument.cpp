#include "freeformselectioninstrument.h"
#include "../imagearea.h"
#include "../undocommand.h"
#include "math.h"

#include <QPainter>
#include <QApplication>
#include <QClipboard>

FreeformSelectionInstrument::FreeformSelectionInstrument(QObject *parent) :
    AbstractSelection(parent)
{
}

void FreeformSelectionInstrument::copyImage(ImageArea &imageArea)
{
    if (mIsSelectionExists)
    {
        imageArea.setImage(mImageCopy);
        QClipboard *globalClipboard = QApplication::clipboard();
        QImage copyImage;
        if(mIsImageSelected)
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

void FreeformSelectionInstrument::cutImage(ImageArea &imageArea)
{
    if (mIsSelectionExists)
    {
        copyImage(imageArea);
        if(mIsSelectionExists)
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

void FreeformSelectionInstrument::pasteImage(ImageArea &imageArea)
{
    QClipboard *globalClipboard = QApplication::clipboard();
    if(mIsSelectionExists)
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

void FreeformSelectionInstrument::startAdjusting(ImageArea &imageArea)
{
    mImageCopy = *imageArea.getImage();
    mIsImageSelected = false;
}

void FreeformSelectionInstrument::startSelection(ImageArea &)
{
}

void FreeformSelectionInstrument::startResizing(ImageArea &imageArea)
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

void FreeformSelectionInstrument::startMoving(ImageArea &imageArea)
{
    clearSelectionBackground(imageArea);
    if (mIsSelectionAdjusting)
    {
        mIsImageSelected = false;
    }
}

void FreeformSelectionInstrument::select(ImageArea &)
{
}

void FreeformSelectionInstrument::resize(ImageArea &)
{
}

void FreeformSelectionInstrument::move(ImageArea &)
{
}

void FreeformSelectionInstrument::completeSelection(ImageArea &imageArea)
{
    mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
                                                mTopLeftPoint.y(),
                                                mWidth, mHeight);
    emit sendEnableCopyCutActions(true);
}

void FreeformSelectionInstrument::completeResizing(ImageArea &imageArea)
{
    mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
                                                mTopLeftPoint.y(),
                                                mWidth, mHeight);
}

void FreeformSelectionInstrument::completeMoving(ImageArea &imageArea)
{
    if (mIsSelectionAdjusting)
    {
        mSelectedImage = imageArea.getImage()->copy(mTopLeftPoint.x(),
                                                   mTopLeftPoint.y(),
                                                   mWidth, mHeight);
    }

}

void FreeformSelectionInstrument::clearSelectionBackground(ImageArea &imageArea)
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

void FreeformSelectionInstrument::clear()
{
    mSelectedImage = QImage();
    emit sendEnableCopyCutActions(false);
}

void FreeformSelectionInstrument::paint(ImageArea &imageArea, bool, bool)
{
    if (mIsSelectionExists && !mIsSelectionAdjusting)
    {
        if(mTopLeftPoint != mBottomRightPoint)
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

void FreeformSelectionInstrument::showMenu(ImageArea &)
{
}

void FreeformSelectionInstrument::drawBorder(ImageArea &imageArea)
{
	if (mWidth > 1 && mHeight > 1)
	{
		QPainter painter(imageArea.getImage());
		painter.setPen(QPen(Qt::blue, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
		painter.setBackgroundMode(Qt::TransparentMode);
		if (mTopLeftPoint != mBottomRightPoint)
		{
			painter.drawRect(QRect(mTopLeftPoint, mBottomRightPoint - QPoint(1, 1)));
			//painter.drawRect(QRect(QPoint(minX,minY), QPoint(maxX,maxY) - QPoint(1, 1)));
			//painter.drawLine(mStartPoint, mEndPoint);
			
		}
		imageArea.setEdited(true);
		painter.end();
		imageArea.update();
	}
}

void FreeformSelectionInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
	mButton = event->button();
	mIsMouseMoved = false;
	if (mIsSelectionExists)
	{
		imageArea.setImage(mImageCopy);
		paint(imageArea);
		if (mButton == Qt::RightButton)
		{
			mIsSelectionAdjusting = true;
			startAdjusting(imageArea);
		}
		if (event->pos().x() > mTopLeftPoint.x() &&
			event->pos().x() < mBottomRightPoint.x() &&
			event->pos().y() > mTopLeftPoint.y() &&
			event->pos().y() < mBottomRightPoint.y())
		{
			if (!mIsSelectionAdjusting)
			{
				makeUndoCommand(imageArea);
			}
			if (!mIsImageSelected)
			{
				startMoving(imageArea);
				if (!mIsSelectionAdjusting)
				{
					mIsImageSelected = true;
				}
			}
			else
			{
				drawBorder(imageArea);
			}
			mIsSelectionMoving = true;
			mMoveDiffPoint = mBottomRightPoint - event->pos();
			return;
		}
		else if (event->pos().x() >= mBottomRightPoint.x() &&
			event->pos().x() <= mBottomRightPoint.x() + 6 &&
			event->pos().y() >= mBottomRightPoint.y() &&
			event->pos().y() <= mBottomRightPoint.y() + 6)
		{
			if (!mIsSelectionAdjusting)
			{
				makeUndoCommand(imageArea);
			}
			startResizing(imageArea);
			mIsSelectionResizing = true;
			return;
		}
		else
		{
			clearSelection(imageArea);
		}
	}
	if (event->button() == Qt::LeftButton)
	{
		mBottomRightPoint = mTopLeftPoint = mStart = mEnd = event->pos();
		minX = maxX = event->pos().x();
		minY = maxY = event->pos().y();
		mHeight = mWidth = 0;
		mImageCopy = *imageArea.getImage();
		startSelection(imageArea);
		mIsPaint = true;
	}
}

void FreeformSelectionInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
	mIsMouseMoved = true;
	if (mIsSelectionExists)
	{
		if (mIsSelectionMoving)
		{
			mBottomRightPoint = event->pos() +
				mMoveDiffPoint;
			maxX = mBottomRightPoint.x();
			maxY = mBottomRightPoint.y();
			mTopLeftPoint = event->pos() + mMoveDiffPoint -
				QPoint(mWidth - 1, mHeight - 1);
			minX = mTopLeftPoint.x();
			minY = mTopLeftPoint.y();
			imageArea.setImage(mImageCopy);
			move(imageArea);
			drawBorder(imageArea);
			mIsPaint = false;
		}
		else if (mIsSelectionResizing)
		{
			mBottomRightPoint = event->pos();
			maxX = mBottomRightPoint.x();
			maxY = mBottomRightPoint.y();
			mHeight = fabs(mTopLeftPoint.y() - mBottomRightPoint.y()) + 1;
			mWidth = fabs(mTopLeftPoint.x() - mBottomRightPoint.x()) + 1;
			imageArea.setImage(mImageCopy);
			resize(imageArea);
			drawBorder(imageArea);
			mIsPaint = false;
		}
	}
	if (mIsPaint)
	{
		mBottomRightPoint = event->pos();
		mEnd = event->pos();
		minX = qMin(minX, mEnd.x());
		minY = qMin(minY, mEnd.y());
		maxX = qMax(maxX, mEnd.x());
		maxY = qMax(maxY, mEnd.y());
		mBottomRightPoint = QPoint(maxX, maxY);
		mTopLeftPoint = QPoint(minX, minY);
		mHeight = fabs(mTopLeftPoint.y() - mBottomRightPoint.y()) + 1;
		mWidth = fabs(mTopLeftPoint.x() - mBottomRightPoint.x()) + 1;
		imageArea.setImage(mImageCopy);
		drawBorder(imageArea);
		select(imageArea);
		mStart = event->pos();
	}
	updateCursor(event, imageArea);
}

void FreeformSelectionInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
	int right = mTopLeftPoint.x() > mBottomRightPoint.x() ? mTopLeftPoint.x() : mBottomRightPoint.x();
	int bottom = mTopLeftPoint.y() > mBottomRightPoint.y() ? mTopLeftPoint.y() : mBottomRightPoint.y();
	int left = mTopLeftPoint.x() < mBottomRightPoint.x() ? mTopLeftPoint.x() : mBottomRightPoint.x();
	int top = mTopLeftPoint.y() < mBottomRightPoint.y() ? mTopLeftPoint.y() : mBottomRightPoint.y();
	mBottomRightPoint = QPoint(maxX, maxY);
	mTopLeftPoint = QPoint(minX, minY);
	if (mIsSelectionExists)
	{
		updateCursor(event, imageArea);
		if (mButton == Qt::RightButton && !mIsMouseMoved)
		{
			showMenu(imageArea);
			paint(imageArea);
			drawBorder(imageArea);
			mIsPaint = false;
			mIsSelectionMoving = mIsImageSelected = false;
		}
		else if (mIsSelectionMoving)
		{
			imageArea.setImage(mImageCopy);
			completeMoving(imageArea);
			paint(imageArea);
			drawBorder(imageArea);
			mIsPaint = false;
			mIsSelectionMoving = false;
		}
		else if (mIsSelectionResizing)
		{
			imageArea.setImage(mImageCopy);
			paint(imageArea);
			completeResizing(imageArea);
			paint(imageArea);
			drawBorder(imageArea);
			mIsPaint = false;
			mIsSelectionResizing = false;
		}
	}
	if (mIsPaint)
	{
		if (event->button() == Qt::LeftButton)
		{
			imageArea.setImage(mImageCopy);
			if (mTopLeftPoint != mBottomRightPoint)
			{
				imageArea.setImage(mImageCopy);
				paint(imageArea);
				completeSelection(imageArea);
				paint(imageArea);
				mIsSelectionExists = true;
			}
			drawBorder(imageArea);
			mIsPaint = false;
		}
	}
	mIsSelectionAdjusting = false;
}
