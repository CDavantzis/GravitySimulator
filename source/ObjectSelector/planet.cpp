
#include "planet.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>



Planet::Planet(): color(Qt::white){
}

Planet::Planet(QColor color): color(color){

}


QRectF Planet::boundingRect() const
{
    qreal adjust = 1;
    return QRectF(-10 - adjust, -10 - adjust, 20 + adjust, 20 + adjust);
    return QRectF();

}

QPainterPath Planet::shape() const
{
    QPainterPath path;
    path.addRect(-10, -10, 20, 20);
    return path;
}

void Planet::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(color);
    painter->drawEllipse(-10, -10, 20, 20);
}

#include <QDebug>


void Planet::advance(int step)
{

    if (!step)
        return;



    //setPos(mapToParent(0, 1));
    setPos(mapToParent(0, double(qrand())/1000000));

}
