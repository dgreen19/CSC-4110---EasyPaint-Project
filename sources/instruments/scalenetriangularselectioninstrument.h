#ifndef SCALENETRIANGULARSELECTIONINSTRUMENT_H
#define SCALENETRIANGULARSELECTIONINSTRUMENT_H

#include "abstractselection.h"

QT_BEGIN_NAMESPACE
class QUndoStack;
QT_END_NAMESPACE

class ScaleneTriangularSelectionInstrument : public AbstractSelection
{
	Q_OBJECT

public:
	explicit ScaleneTriangularSelectionInstrument(QObject *parent = 0);

	void clearSelectionBackground(ImageArea &imageArea);
	void copyImage(ImageArea &imageArea);
	void pasteImage(ImageArea &imageArea);
	void cutImage(ImageArea &imageArea);
	void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

signals:
	void sendCloseTextDialog();

protected:
	void paint(ImageArea &imageArea, bool = false, bool = false);
	void drawBorder(ImageArea &imageArea);

private:
	void startAdjusting(ImageArea &imageArea);
	void startSelection(ImageArea &);
	void startResizing(ImageArea &imageArea);
	void startMoving(ImageArea &imageArea);
	void select(ImageArea &);
	void resize(ImageArea &);
	void move(ImageArea &);
	void completeSelection(ImageArea &imageArea);
	void completeResizing(ImageArea &imageArea);
	void completeMoving(ImageArea &imageArea);
	void clear();

	void showMenu(ImageArea &);
	QPoint mFirstControlPoint;
	QString mText;
	unsigned int mPointsCount : 2; /*< Changes from 0 to 2, so 2 bits is enough. */

	QImage mSelectedImage, /**< Copy of selected image. */
		mPasteImage; /**< Image to paste */

signals:
	void sendEnableCopyCutActions(bool enable);
	void sendEnableSelectionInstrument(bool enable);

};

#endif // SELECTIONINSTRUMENT_H
