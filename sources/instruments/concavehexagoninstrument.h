#ifndef CONCAVEHEXAGONINSTRUMENT_H
#define CONCAVEHEXAGONINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Concave Hexagon Instrument class.
 *
 */
class ConcaveHexagonInstrument : public AbstractInstrument
{
	Q_OBJECT
public:
	explicit ConcaveHexagonInstrument(QObject *parent = 0);

	void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
	void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

};

#endif
#pragma once
#pragma once
