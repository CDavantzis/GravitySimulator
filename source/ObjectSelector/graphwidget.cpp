#include "graphwidget.h"
#include "body.h"

#include <math.h>
#include <QKeyEvent>
#include <QDebug>
#include <QTime>
#include <QThread>

GraphWidget::GraphWidget(QWidget *parent): QGraphicsView(parent), timerId(0){
    //Configure GraphWidget Scene
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-4000, -4000, 8000, 8000);
    setScene(scene);
    QList<Body*> bodies;
}


void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        break;
    case Qt::Key_Down:
        break;
    case Qt::Key_Left:
        break;
    case Qt::Key_Right:
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);

    //Framerate management
    int elapsed = ElapsedTime.elapsed();
    if (elapsed <= 40){
        QThread::msleep(40-elapsed);
    }
    elapsed = ElapsedTime.restart();
    int framerate = int((double(elapsed)/40)*100);


    //Get Bodies
    QList<Body *> bodies;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Body *body = qgraphicsitem_cast<Body *>(item))
            bodies << body;
    }

    //BRUTEFORCE
    //Calculate New Postions
    foreach (Body *body, bodies)
        body->calculateForces();
    //Move To New Postition
    foreach (Body *body, bodies)
        body->advance();


}



#ifndef QT_NO_WHEELEVENT
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect){
    painter->fillRect(rect, Qt::black);
    painter->setPen(QPen(Qt::white, 1));
    painter->drawLine(0,rect.top(),0,rect.bottom()); //vertical
    painter->drawLine(rect.left(),0,rect.right(),0); //horizontal
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;
    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    int width = this->viewport()->width();
    int height =this->viewport()->height();
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Body *body = qgraphicsitem_cast<Body *>(item)){
            body->setPos(-(width/2) + (qrand() %width), - (height/2) + qrand() % (height)); //Move body to random position
            body->vectVel = QPointF(0,0); //zero velocity vector
        }
    }
}

void GraphWidget::zoomIn(){
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut(){
    scaleView(1 / qreal(1.2));

}


void GraphWidget::addBody(int index){
    Body *planet = new Body(index,table,this);
    scene()->addItem(planet);
}

void GraphWidget::removeBody(int index){
    scene()->removeItem(scene()->items().back());
}


void GraphWidget::animate(bool a){
    if (a){
        //start timer for animation
        timerId = startTimer(0);
        ElapsedTime.start();
    }
    else{
        //stop timer for animation
        killTimer(timerId);
        timerId = 0;
    }
}

