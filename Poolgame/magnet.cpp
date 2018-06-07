#include "magnet.h"
#include <qDebug>

// draw the manget as small grey balls
void Magnet::render(QPainter &painter, const QVector2D &offset){
    painter.setBrush(QColor("grey"));
    painter.drawEllipse((m_pos+offset).toPointF(), m_radius, m_radius);
}
