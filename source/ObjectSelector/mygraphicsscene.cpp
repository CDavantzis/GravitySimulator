#include "mygraphicsscene.h"
#include "mygraphicsview.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "qdebug.h"
#include "body.h"

#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>


MyGraphicsScene::MyGraphicsScene(QObject* parent, MyGraphicsView*myView): QGraphicsScene(parent), myView(myView){
    //Setup Scene
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(-4000, -4000, 8000, 8000);
    //Setup BodyLauncher
    body_launcher = new BodyLauncher();
    this->addItem(body_launcher);
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    switch (event->button()) {
    case Qt::RightButton:
        body_launcher->grab(event);
        break;
    default:
        QGraphicsScene::mousePressEvent(event);
    }
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    mousePos = event->scenePos();
    if (body_launcher->isVisible()){
        body_launcher->stretch(event);
    }
    else{
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QPointF pos;
    QPointF vel;
    switch (event->button()) {
    case Qt::RightButton:
        body_launcher->release(event,pos,vel);
        addBody(pos,vel);
        break;
   default:
        QGraphicsScene::mousePressEvent(event);
    }
}


void MyGraphicsScene::addBody(){
    Body *body = new Body();
    addItem(body);
}

void MyGraphicsScene::addBody(QPointF pos, QPointF vel){
    Body *body = new Body();
    body->setPos(pos);
    body->vel = vel;
    addItem(body);
}


