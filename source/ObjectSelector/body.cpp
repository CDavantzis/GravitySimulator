#include "body.h"
#include "graphwidget.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <cmath>

const qreal G = 6.674e-11;

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

        vectVel = QPointF(0,0); //zero velocity vector
}


void  Body::setMass(qreal mass){
    this->mass = mass;
    this->radius = mass / 10;
    this->table_items[0]->setText(QString::number(mass));
    update();
}



QRectF Body::boundingRect() const{
    //Outer bounds of item as a rectangle, used for redrawing;
    return QRectF(-radius-1,-radius-1,2*radius+2,2*radius+2);
}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    painter->drawEllipse(QRectF(-radius,-radius,2*radius,2*radius));
    //painter->setFont(QFont("Arial",radius));
     //painter->drawText(this->boundingRect(), Qt::AlignCenter, QString::number(this->table_row));
}


QVariant Body::itemChange(GraphicsItemChange change, const QVariant &value){
    //Called when item's state changes
    if (change == ItemPositionHasChanged){
        //Update table cell values
        this->table_items[1]->setText(QString::number(pos().x()));    //Location X
        this->table_items[2]->setText(QString::number(-pos().y()));   //Location Y
        this->table_items[3]->setText(QString::number(vectVel.x()));  //Velocity X
        this->table_items[4]->setText(QString::number(-vectVel.y())); //Velocity Y
        this->update();
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
    //Calculate the forces acting on object and determine new postion.

    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }

    if (!graph->forceOption_cumulative){
        vectVel = QPointF(0,0); //zero velocity vector
    }

    QPointF vectPosChange = QPointF(0,0); //Position change vector.

    foreach (QGraphicsItem *item, scene()->items()) {
        Body *other = qgraphicsitem_cast<Body *>(item);

        if ((!other) || (this == other)){
            //skip calculation if other is not a body or if the other is this body;
            continue;
        }

        QPointF vectDist =  graph->forceOption_reverse ? this->mapToItem(other, 0, 0) : other->mapToItem(this,0,0); //Distance Vector.
        qreal dist = sqrt(pow(vectDist.x(), 2) + pow(vectDist.y(), 2)); //Distance between bodies

        //Soften distance
        dist = qMax(dist, this->radius+other->radius);

        qreal F = G*((this->mass*other->mass)/(dist*dist));
        QPointF vectForce = F * vectDist / dist;

        vectVel += graph->dt * vectForce / mass;
        vectPosChange += graph->dt *  vectVel;
    }
    newPos = pos() + QPointF(vectPosChange.x(), vectPosChange.y());
}

