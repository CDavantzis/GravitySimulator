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

Body::Body(MyGraphicsScene *myScene, int index):myScene(myScene){
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
    painter->setBrush(Qt::white);
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
        //this->update();
    }
    return QGraphicsItem::itemChange(change, value);
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


void Body::getNewPos(){
    //Use bruteforce for N-Body calculations;
    if (scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }
    if (myScene->bodies.count() == 1){
        newPos = pos() - dT*vel;
        return;
    }
    QPointF PosChange = QPointF(0,0); //Position change vector.
    foreach (Body *other, myScene->bodies)
        PosChange += calcPosChangeFrom(other);
    newPos = pos() - PosChange;
}

void Body::moveToNewPos(){
    //Move body to newPos;
    if(exist){
        setPos(newPos); //Move to newPos
        return;
    }
    myScene->removeBody(this);
    delete this;
}
inline QPointF Body::calcPosChangeFrom(Body *other){
    //Calulate position change from other body
    if (this == other)
        return QPointF(0,0);
    QPointF vectDist = mapToItem(other,0,0); //Distance Vector.
    qreal dist = sqrt(pow(vectDist.x(), 2) + pow(vectDist.y(), 2)); //Distance between bodies
    if ((canCollide) && (dist <= this->radius+other->radius))
        collide(other);
    dist = qMax(dist, this->radius+other->radius); //Soften distance
    vel += dT*((G*((this->mass*other->mass)/(dist*dist))) * vectDist / dist)/ mass;
    return dT*vel;
}
