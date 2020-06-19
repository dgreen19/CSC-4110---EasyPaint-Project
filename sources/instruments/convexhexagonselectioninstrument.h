//ADDED BY DARRYL GREEN FOR CONVEX HEXAGON SELECTION INSTRUMENT
#ifndef CONCAVEHEXAGONSELECTIONINSTRUMENT_H
#define CONCAVEHEXAGONSELECTIONINSTRUMENT_H

#include "abstractselection.h"

QT_BEGIN_NAMESPACE
class QUndoStack;
QT_END_NAMESPACE

class ConvexHexagonSelectionInstrument : public AbstractSelection
{
	Q_OBJECT

public:
	explicit ConvexHexagonSelectionInstrument(QObject *parent = 0);

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

	QImage mSelectedImage, //Copy of selected image
		mPasteImage; //Pastes image

signals:
	void sendEnableCopyCutActions(bool enable);
	void sendEnableSelectionInstrument(bool enable);

};

#endif // SELECTIONINSTRUMENT_H
#pragma once
