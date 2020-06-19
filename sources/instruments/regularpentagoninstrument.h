#ifndef REGULARPENTAGONINSTRUMENT_H
#define REGULARPENTAGONINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief RegularPentagon instrument class.
 *
 */
class RegularPentagonInstrument : public AbstractInstrument
{
	Q_OBJECT
public:
	explicit RegularPentagonInstrument(QObject *parent = 0);

	void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
	void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

};

#endif