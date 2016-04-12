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
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect());
    //painter->setFont(QFont("Arial",radius));
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


    QPointF vecV = QPointF(0,0);
    QPointF vecR = QPointF(0,0);
    qreal m1 = this->mass;
    qreal r1 = this->mass / 5;

    foreach (QGraphicsItem *item, scene()->items()) {
        Body *body = qgraphicsitem_cast<Body *>(item);
        if (!body){
            //skip calculation if qgraphicsitem is not a body
            continue;
        }
        if (this == body){
            //skip calculation if the other body is this body.
            continue;
        }

       // if (this->collidesWithItem(body)){
       //     continue;
       // }


        QPointF vecD;
        if (!graph->reverse_forces){
            vecD = body->mapToItem(this,0,0);
        }
        else{
            vecD = mapToItem(body, 0, 0);
        }


        qreal dist = sqrt(pow(vecD.x(), 2) + pow(vecD.y(), 2));

        qreal m2 = body->mass;
        qreal r2 = body->mass/5;

        if (dist < r1+r2){
            //Softening based on distance to center
            dist = r1+r2;
        }

        qreal F = G*((m1*m2)/(dist*dist));
        QPointF vecF = F * vecD / dist;

        vecV += dt * vecF / mass;
        vecR += dt * vecV;
    }

    QPointF change_in_distance = QPointF(vecR.x(), vecR.y());
    newPos = pos() + change_in_distance;

}

void Body::handleCollision(){



}
