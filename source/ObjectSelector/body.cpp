#include "body.h"
#include "graphwidget.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <cmath>
Body::Body(int current_index, QTableWidget *table,GraphWidget *graphWidget):
    graph(graphWidget),
    table_row(current_index),
    color(Qt::white){
        int column_count = table->columnCount();
        for (int i = 0; i < column_count; i++){
            table_items.append(table->item(current_index,i));
        }
        setFlag(ItemIsMovable);
        setFlag(ItemSendsGeometryChanges);
        setCacheMode(DeviceCoordinateCache);
        setZValue(-1);
        setPos(0,0);
        setMass(100);
}


void  Body::setMass(double mass){
    this->mass = mass;
    this->table_items[0]->setText(QString::number(mass));
    update();
}


QRectF Body::boundingRect() const{
    int radius = mass / 5;
    return QRectF(-radius,-radius,2*radius,2*radius);
}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(boundingRect());
    painter->setPen(Qt::black);
    painter->setFont(QFont("Arial",radius));
    //painter->drawText(this->boundingRect(), Qt::AlignCenter, QString::number(this->table_row));
}

QVariant Body::itemChange(GraphicsItemChange change, const QVariant &value){
    //Called when item's state changes
    if (change == ItemPositionHasChanged){
        //Update table values with changed position
        this->table_items[1]->setText(QString::number(pos().x()));
        this->table_items[2]->setText(QString::number(-pos().y()));
    }
    return QGraphicsItem::itemChange(change, value);
}




bool Body::advance()
{
    if (newPos == pos())
        return false;
    setPos(newPos);
    return true;
}

void Body::calculateForces(){
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }

    qreal G = 6.674e-11;
    qreal dt = graph->dt;
    qreal xvel = 0;
    qreal yvel = 0;
    qreal Vx = 0;
    qreal Vy = 0;
    qreal Rx = 0;
    qreal Ry = 0;

    foreach (QGraphicsItem *item, scene()->items()) {
        Body *body = qgraphicsitem_cast<Body *>(item);
        if (!body)
            continue;
        if (this == body)
            continue;

        QPointF vec = mapToItem(body, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        qreal dist = sqrt(pow(dx, 2) + pow(dy, 2));


        qreal m1 = this->mass * pow(10,24);
        qreal m2 = body->mass * pow(10,24);

        qreal F = (G * m1 * m2) / (pow(dist, 2));
        qreal Fx = F * dx / dist;
        qreal Fy = F * dy / dist;
        Vx += dt * Fx / mass;
        Vy += dt * Fy / mass;
        Rx += dt * Vx;
        Ry += dt * Vy;

    }

    //newPos = this->pos();
    newPos = this->pos() + QPointF(Rx * 10e-59, Ry * 10e-59);

}

