#ifndef CONVEXHEXAGONINSTRUMENT_H
#define CONVEXHEXAGONINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief Convex Hexagon instrument class.
 *
 */
class ConvexHexagonInstrument : public AbstractInstrument
{
	Q_OBJECT
public:
	explicit ConvexHexagonInstrument(QObject *parent = 0);

	void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
	void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

};

#endif
#pragma once
