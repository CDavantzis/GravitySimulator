#include "mygraphicsview.h"
#include "mygraphicsscene.h"
#include "body.h"

MyGraphicsView::MyGraphicsView(QWidget *parent): QGraphicsView(parent), timerId(0){
    setScene(new MyGraphicsScene(this));
}

void MyGraphicsView::keyPressEvent(QKeyEvent *event){
    switch (event->key()){
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void MyGraphicsView::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);
    Body::dT = dT.restart()*10000;
    Body::step();
}

#ifndef QT_NO_WHEELEVENT
void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif

void MyGraphicsView::drawBackground(QPainter *painter, const QRectF &rect){
    painter->fillRect(rect, Qt::black);
    painter->setPen(QPen(Qt::white, 1));
    painter->drawLine(0,rect.top(),0,rect.bottom()); //vertical
    painter->drawLine(rect.left(),0,rect.right(),0); //horizontal
}

void MyGraphicsView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;
    scale(scaleFactor, scaleFactor);
}


void MyGraphicsView::zoomIn(){
    scaleView(qreal(1.2));
}

void MyGraphicsView::zoomOut(){
    scaleView(1 / qreal(1.2));
}

void MyGraphicsView::animate(bool a = true){
    // Start and stop animation
    if (a){
        timerId = startTimer(0);
        dT.start();
    }
    else{
        killTimer(timerId);
        timerId = 0;
    }
}
