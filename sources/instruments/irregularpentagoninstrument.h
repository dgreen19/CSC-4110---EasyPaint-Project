#ifndef IRREGULARPENTAGONINSTRUMENT_H
#define IRREGULARPENTAGONINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief IrregularPentagon instrument class.
 *
 */
class IrregularPentagonInstrument : public AbstractInstrument
{
	Q_OBJECT
public:
	explicit IrregularPentagonInstrument(QObject *parent = 0);

	void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
	void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

};

#endif
