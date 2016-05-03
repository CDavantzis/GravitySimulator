#include "mygraphicsscene.h"
#include "launcher.h"

MyGraphicsScene::MyGraphicsScene(QObject* parent): QGraphicsScene(parent){
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(-4000, -4000, 8000, 8000);
    launcher = new Launcher();
    this->addItem(launcher);
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    switch (event->button()) {
    case Qt::RightButton:
        launcher->grab(event->scenePos());
        break;
    default:
        QGraphicsScene::mousePressEvent(event);
    }
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    if (launcher->isVisible()){
        launcher->stretch(event->scenePos());
        return;
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    switch (event->button()) {
        case Qt::RightButton:
            launcher->release();
            break;
        default:
            QGraphicsScene::mouseReleaseEvent(event);
    }
}
