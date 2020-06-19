#ifndef CONVEXPENTAGONINSTRUMENT_H
#define CONVEXPENTAGONINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief ConvexPentagon instrument class.
 *
 */
class ConvexPentagonInstrument : public AbstractInstrument
{
	Q_OBJECT
public:
	explicit ConvexPentagonInstrument(QObject *parent = 0);

	void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
	void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

};

#endif
