#include "body.h"
#include "mygraphicsview.h"
#include "mygraphicsscene.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <cmath>
#include <mutex>
const qreal G = 6.674e-11;
const qreal PI = 3.14159265359;

bool Body::canCollide;
int Body::dT;

static std::mutex m1;

QList<Body*>    Body::list;
QTableWidget*   Body::table;
MyGraphicsView* Body::view;


void Body::push_back(){
    Body *body = new Body();
    view->scene()->addItem(body);
}


void Body::pop_back(){
    if (table->rowCount() > 0){
        list.last()->Remove();
    }
}

Body::Body(){
    int cols = table->columnCount();
    int rows = table->rowCount();
    table->insertRow(rows);

    for (int col = 0; col < cols ; ++col){
        table->setItem(rows,col,new QTableWidgetItem("0"));
        table_items.append(table->item(rows,col));
    }


    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setPos(0,0);
    setMass(100);
    setRadius(15);
    vel = QPointF(0,0); //zero velocity vector
    exist = true;
    list.append(this);
}

void Body::Remove(){

        int index = list.indexOf(this);
        table->removeRow(index);
        list.removeAt(index);
        this->scene()->removeItem(this);
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
    this->table_items[0]->setText(QString::number(mass));
    //update();
}

void Body::setRadius(qreal radius){
    this->radius = radius;
    this->table_items[1]->setText(QString::number(radius));
    update();
}

QVariant Body::itemChange(GraphicsItemChange change, const QVariant &value){
    if (change == ItemPositionHasChanged){
        //Update table cell values
        this->table_items[2]->setText(QString::number(pos().x()));    //Location X
        this->table_items[3]->setText(QString::number(-pos().y()));   //Location Y
        this->table_items[4]->setText(QString::number(vel.x()));  //Velocity X
        this->table_items[5]->setText(QString::number(-vel.y())); //Velocity Y
    }
    return QGraphicsItem::itemChange(change, value);
}

void Body::collide(Body *other){
    //Collide this with other;

    m1.lock();
    if(this->exist && other->exist) {
        qreal newRadius = sqrt(this->radius*this->radius + other->radius*other->radius);
        if (this->radius >=other->radius){
            this->setMass(this->mass + other->mass);
            this->setRadius(newRadius);
            this->vel = ((this->mass*this->vel)+(other->mass*other->vel))/(this->mass+other->mass);     //inelastic collision v=(m1*v1+m2*v2)/(m1+m2)
            other->exist = false;
        }
        else{
            other->setMass(this->mass + other->mass);
            other->setRadius(newRadius);
            other->vel = ((this->mass*this->vel)+(other->mass*other->vel))/(this->mass+other->mass);    //inelastic collision v=(m1*v1+m2*v2)/(m1+m2)
            this->exist = false;
        }
    }
    m1.unlock();
}


void Body::getNewPos(){
    //Use bruteforce for N-Body calculations;
    if (scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }
    if (list.count() == 1){
        newPos = pos() - dT*vel;
        return;
    }
    QPointF PosChange = QPointF(0,0); //Position change vector.
    foreach (Body *body, list)
        PosChange += calcPosChangeFrom(body);
    newPos = pos() - PosChange;
}

void Body::moveToNewPos(){
    //Move body to newPos;
    if(exist){
        setPos(newPos); //Move to newPos
        update(); //update everytime to fix collision glitches.
        return;
    }
    this->Remove();
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
