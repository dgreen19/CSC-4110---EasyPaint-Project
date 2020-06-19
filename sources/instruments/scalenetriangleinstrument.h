#ifndef SCALENETRIANGLEINSTRUMENT_H
#define SCALENETRIANGLEINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Scalene Triangle instrument class.
 *
 */
class ScaleneTriangleInstrument : public AbstractInstrument
{
	Q_OBJECT
public:
	explicit ScaleneTriangleInstrument(QObject *parent = 0);

	void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

signals:
	void sendCloseTextDialog();

protected:
	void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

private:
	QPoint mFirstControlPoint;
	QString mText;
    unsigned int mPointsCount : 2; /*< Changes from 0 to 2, so 2 bits is enough. */

private slots:
	void updateText(ImageArea *, QString);

};

#endif // SCALENETRIANGLEINSTRUMENT_H
