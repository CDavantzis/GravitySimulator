#include "body.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>


Body::Body(double mass, double radius, double x, double y):mass(mass), radius(radius),color(Qt::white){
    //QGraphicsScene y-axis grows downward
    setPos(x,-y);
}

Body::Body(QTableWidget *table,int index):index(index),color(Qt::white){
    mass = table->item(index,0)->text().toInt();
    //radius = table->item(index,1)->text().toInt();
   radius = 10;

    int x = table->item(index,2)->text().toInt();
    int y = table->item(index,3)->text().toInt();
    setPos(x,y);

}

void  Body::setRadius(double radius){
    this->radius = radius;
    update();
}



QRectF Body::boundingRect() const{
    return QRectF(-radius,-radius,2*radius,2*radius);
}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(boundingRect());
}

void Body::advance(int step)
{
    if (!step)
        return;
    //moveBy(1,-1);

    setPos(mapToParent(1, -1));

}




