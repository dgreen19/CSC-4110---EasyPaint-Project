#ifndef CONCAVEPENTAGONINSTRUMENT_H
#define CONCAVEPENTAGONINSTRUMENT_H

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
 * @brief ConcavePentagon instrument class.
 *
 */
class ConcavePentagonInstrument : public AbstractInstrument
{
    Q_OBJECT
public:
    explicit ConcavePentagonInstrument(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

};

#endif
