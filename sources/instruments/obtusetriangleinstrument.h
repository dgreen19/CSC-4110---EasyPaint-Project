#ifndef OBTUSETRIANGLEINSTRUMENT_H
#define OBTUSETRIANGLEINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

 /**
  * @brief Obtuse Triangle instrument class.
  *
  */
class ObtuseTriangleInstrument : public AbstractInstrument
{
	Q_OBJECT
public:
	explicit ObtuseTriangleInstrument(QObject *parent = 0);

	void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
	void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

private:
	QPoint mFirstControlPoint;
	QPoint mLastDrawn;
	QString mText;
	int mAngle;
	unsigned int mPointsCount : 2; /*< Changes from 0 to 2, so 2 bits is enough. */

signals:
	void sendCloseTextDialog();

private slots:
	void updateText(ImageArea *, QString);
	void updateAngle(ImageArea *, int);

};

#endif // OBTUSETRIANGLEINSTRUMENT_H
