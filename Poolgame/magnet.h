#ifndef MAGNET_H
#define MAGNET_H
#include <qDebug>
#include <QVector2D>
#include <QPainter>
#include <QBrush>

class Magnet
{
private:
    QVector2D m_pos;
    double m_radius;
public:
    Magnet(QVector2D pos,double radius):m_pos(pos),m_radius(radius){}
    /**
     * @brief render a grey ball to represent the magnet
     * @param painter
     * @param offset
     */
    void render(QPainter& painter, const QVector2D& offset);

    QVector2D getPos(){return m_pos;}
    double getRadius(){return m_radius;}
};

#endif // MAGNET_H
