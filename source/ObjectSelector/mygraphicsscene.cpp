#include "mygraphicsscene.h"
#include "mygraphicsview.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "qdebug.h"
#include "body.h"

#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>


MyGraphicsScene::MyGraphicsScene(QObject* parent): QGraphicsScene(parent){
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(-4000, -4000, 8000, 8000);
    body_launcher = new BodyLauncher();
    this->addItem(body_launcher);
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    switch (event->button()) {
    case Qt::RightButton:
        body_launcher->grab(event->scenePos());
        break;
    default:
        QGraphicsScene::mousePressEvent(event);
    }
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    if (body_launcher->isVisible()){
        body_launcher->stretch(event->scenePos());
        return;
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    switch (event->button()) {
        case Qt::RightButton:
            body_launcher->release();
            break;
        default:
            QGraphicsScene::mouseReleaseEvent(event);
    }
}






