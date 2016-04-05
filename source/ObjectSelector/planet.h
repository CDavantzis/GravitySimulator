#ifndef PLANET_H
#define PLANET_H

#include <QGraphicsItem>

class Planet : public QGraphicsItem
{
public:
    Planet();
    Planet(QColor);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void advance(int step) Q_DECL_OVERRIDE;

private:
    qreal speed;
    QColor color;
};

#endif
