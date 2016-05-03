#include "launcher.h"
#include "body.h"
#include "mygraphicsview.h"

Launcher::Launcher():start(QPointF(0,0)),end(QPointF(0,0)){
    setVisible(false);
}

QRectF Launcher::boundingRect() const{
  return Body::view->sceneRect();
}

void Launcher::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setPen(QPen(Qt::red,3));
    painter->drawLine(start,end);
    painter->drawEllipse(QRectF(start.x()-14,start.y()-14,2*14,2*14));
}

void Launcher::grab(QPointF Pos){
    setVisible(true);
    start = end = Pos;
}

void Launcher::stretch(QPointF Pos){
    end = Pos;
    update();
}

void Launcher::release(){
    setVisible(false);
    Body::push_back(start,(end-start)*.000000025);
}
