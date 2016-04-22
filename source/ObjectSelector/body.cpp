#include "body.h"
#include "mygraphicsview.h"
#include "mygraphicsscene.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <cmath>
const qreal G = 6.674e-11;

bool Body::canCollide;
int Body::dT;


Body::Body(MyGraphicsScene *myScene, int index):myScene(myScene), color(Qt::white){
    this->index = index;
    int column_count = myScene->table->columnCount();
    for (int i = 0; i < column_count; i++){
        table_items.append(myScene->table->item(index,i));
    }
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setPos(0,0);
    setMass(100);
    vel = QPointF(0,0); //zero velocity vector
    exist = true;
}


QRectF Body::boundingRect() const{
    //outer bounds;
    return QRectF(-radius-1,-radius-1,2*radius+2,2*radius+2);
}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    //Paint instructions;
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(QRectF(-radius,-radius,2*radius,2*radius));
}

void Body::setMass(qreal mass){
    //Set body mass;
    this->mass = mass;
    this->radius = mass / 10;
    this->table_items[0]->setText(QString::number(mass));
    update();
}

QVariant Body::itemChange(GraphicsItemChange change, const QVariant &value){
    if (change == ItemPositionHasChanged){
        //Update table cell values
        this->table_items[1]->setText(QString::number(pos().x()));    //Location X
        this->table_items[2]->setText(QString::number(-pos().y()));   //Location Y
        this->table_items[3]->setText(QString::number(vel.x()));  //Velocity X
        this->table_items[4]->setText(QString::number(-vel.y())); //Velocity Y
        this->update();
    }
    return QGraphicsItem::itemChange(change, value);
}

void Body::step(){
    //Move body to newPos;
    if(exist){
        setPos(newPos); //Move to newPos
        return;
    }
    myScene->removeBody(this);
    delete this;
}


void Body::collide(Body *other){
    //Collide this with other;
    if (this->mass >=other->mass){
        this->setMass(this->mass + other->mass);
        this->vel = ((this->mass*this->vel)+(other->mass*other->vel))/(this->mass+other->mass);     //inelastic collision v=(m1*v1+m2*v2)/(m1+m2)
        other->exist = false;
    }
    else{
        other->setMass(this->mass + other->mass);
        other->vel = ((this->mass*this->vel)+(other->mass*other->vel))/(this->mass+other->mass);    //inelastic collision v=(m1*v1+m2*v2)/(m1+m2)
        this->exist = false;
    }
}

/*
    N-Body Calculation Methods
*/
void Body::bruteforcePos(){
    //Use bruteforce for N-Body calculations;
    if (!scene()) {
        newPos = pos();
        return;
    }
    if (scene()->mouseGrabberItem() == this) {
        //newPos = pos() - forcesFromMouse();
        newPos = pos();
        return;
    }

    QPointF PosChange = QPointF(0,0); //Position change vector.

    if (myScene->bodies.count() == 1){
        PosChange += dT*vel;
    }
    else{
        foreach (Body *other, myScene->bodies) {
            PosChange += forcesFrom(other);
        }
    }
    newPos = pos() - QPointF(PosChange.x(), PosChange.y());
}


inline QPointF Body::forcesFrom(Body *other){
    if (this == other)
        return QPointF(0,0);
    QPointF vectDist = mapToItem(other,0,0); //Distance Vector.
    qreal dist = sqrt(pow(vectDist.x(), 2) + pow(vectDist.y(), 2)); //Distance between bodies
    if ((canCollide) && (dist <= this->radius+other->radius))
        collide(other);
    dist = qMax(dist, this->radius+other->radius); //Soften distance
    qreal F = G*((this->mass*other->mass)/(dist*dist));
    QPointF vectForce = F * vectDist / dist;
    vel += dT*vectForce / mass;
    return dT*vel; //position change
}


inline QPointF Body::forcesFromMouse(){
    QPointF vectDist = this->pos() - myScene->mousePos; //Distance Vector.
    qreal dist = sqrt(pow(vectDist.x(), 2) + pow(vectDist.y(), 2)); //Distance between bodies
    vel += dT*vectDist / dist*.000000000005;
    QPointF vectPosChange = dT*vel;
    return QPointF(vectPosChange.x(), vectPosChange.y());
}


void Body::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
}

void Body::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    //QGraphicsItem::mouseMoveEvent(event);

}

void Body::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    this->setEnabled(false);this->setEnabled(true);
    QGraphicsItem::mouseReleaseEvent(event);
}

void Body::barneshutPos(){
    //Use Barnes–Hut for N-Body calculations;
}

void Body::particlemeshPos(){
    //Use particle mesh for N-Body calculations;
}
