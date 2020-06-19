#ifndef CONCAVEPENTAGONSELECTIONINSTRUMENT_H
#define CONCAVEPENTAGONSELECTIONINSTRUMENT_H

#include "abstractselection.h"

QT_BEGIN_NAMESPACE
class QUndoStack;
QT_END_NAMESPACE

class ConcavePentagonSelectionInstrument : public AbstractSelection
{
	Q_OBJECT

public:
	explicit ConcavePentagonSelectionInstrument(QObject *parent = 0);

	void clearSelectionBackground(ImageArea &imageArea);
	void copyImage(ImageArea &imageArea);
	void pasteImage(ImageArea &imageArea);
	void cutImage(ImageArea &imageArea);

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
	void paint(ImageArea &imageArea, bool = false, bool = false);
	void drawBorder(ImageArea &imageArea);
	void showMenu(ImageArea &);

	QImage mSelectedImage, /**< Copy of selected image. */
		mPasteImage; /**< Image to paste */

signals:
	void sendEnableCopyCutActions(bool enable);
	void sendEnableSelectionInstrument(bool enable);

};

#endif // SELECTIONINSTRUMENT_H
