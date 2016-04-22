#include "spaceship.h"
#include "graphwidget.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <cmath>

const qreal G = 6.674e-11;

Spaceship::Spaceship(GraphWidget *graphWidget, int index):graph(graphWidget), color(Qt::yellow){
        this->index = index;

        int column_count = graph->table->columnCount();
        for (int i = 0; i < column_count; i++){
            table_items.append(graph->table->item(index,i));
        }
        setFlag(ItemIsMovable);
        setFlag(ItemSendsGeometryChanges);
        setCacheMode(DeviceCoordinateCache);
        setZValue(-1);
        setPos(0,0);
        setMass(100);
        vectVel = QPointF(0,0); //zero velocity vector
        destroy_on_next_step = false;
}


void  Spaceship::setMass(qreal mass){
    this->mass = mass;
    this->radius = mass / 10;
    this->table_items[0]->setText(QString::number(mass));
    update();
}



QRectF Spaceship::boundingRect() const{
    //Outer bounds of item as a rectangle, used for redrawing;
    return QRectF(-radius-1,-radius-1,2*radius+2,2*radius+2);
}

void Spaceship::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(QRectF(-radius,-radius,2*radius,2*radius));
    //painter->setFont(QFont("Arial",radius));
    //painter->drawText(this->boundingRect(), Qt::AlignCenter, QString::number(this->table_row));
}


QVariant Spaceship::itemChange(GraphicsItemChange change, const QVariant &value){
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

void Spaceship::step(){
    if(destroy_on_next_step){
        graph->removeBody(this);
        delete this;
    }
    else{
        setPos(newPos); //Move to newPos
    }
}

void Spaceship::calculateForces(){
    //Calculate the forces acting on object and determine new postion.
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }
    if (!graph->forceOption_cumulative){
        vectVel = QPointF(0,0); //zero velocity vector
    }
    QPointF vectPosChange = QPointF(0,0); //Position change vector.

    if (graph->bodies.count() == 1){
        vectPosChange += graph->dt *  vectVel;
    }
    else{
        foreach (Body *other, graph->bodies) {
            if ((!other) || (this == other)){
                //skip calculation if other is not a body or if the other is this body;
                continue;
            }
            QPointF vectDist =  graph->forceOption_reverse ? this->mapToItem(other, 0, 0) : other->mapToItem(this,0,0); //Distance Vector.
            qreal dist = sqrt(pow(vectDist.x(), 2) + pow(vectDist.y(), 2)); //Distance between bodies

            if ((graph->bodies_collide) && (dist <= this->radius+other->radius)){
                collideWith(other);
            }

            dist = qMax(dist, this->radius+other->radius);         //Soften distance
            qreal F = G*((this->mass*other->mass)/(dist*dist));
            QPointF vectForce = F * vectDist / dist;
            vectVel += graph->dt * vectForce / mass;
            vectPosChange += graph->dt *  vectVel;
        }
    }
    newPos = pos() + QPointF(vectPosChange.x(), vectPosChange.y());
}

void Spaceship::mousePressEvent(QGraphicsSceneMouseEvent *event){
    dragStartPos = pos();
    dragTime.start();
    QGraphicsItem::mousePressEvent(event);
}

void Spaceship::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    double t = 0.001*dragTime.elapsed();
    if (t!=0){
        QPointF vectD = QPointF(this->x()-dragStartPos.x(),this->y()-dragStartPos.y());
        QPointF vectA = (2*(vectD-(t*vectVel)))/(t*t);
        //vectVel = (vectA*t)*.0000001;
        //this->table_items[3]->setText(QString::number(vectVel.x()));  //Velocity X
        //this->table_items[4]->setText(QString::number(-vectVel.y())); //Velocity Y
    }
    QGraphicsItem::mouseReleaseEvent(event);
}


void Spaceship::collideWith(Body *other){
    if (this->mass >=other->mass){
        this->setMass(this->mass + other->mass);
        this->vectVel = ((this->mass*this->vectVel)+(other->mass*other->vectVel))/(this->mass+other->mass);     //inelastic collision v=(m1*v1+m2*v2)/(m1+m2)
        other->destroy_on_next_step = true;
    }
    else{
        other->setMass(this->mass + other->mass);
        other->vectVel = ((this->mass*this->vectVel)+(other->mass*other->vectVel))/(this->mass+other->mass);    //inelastic collision v=(m1*v1+m2*v2)/(m1+m2)
        this->destroy_on_next_step = true;
    }
}
