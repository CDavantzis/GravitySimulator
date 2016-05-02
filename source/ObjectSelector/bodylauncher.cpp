#include "bodylauncher.h"
#include "mygraphicsview.h"
#include <QPainter>
#include "qdebug.h"

BodyLauncher::BodyLauncher():start(QPointF(0,0)),end(QPointF(0,0)){
    setVisible(false);
}

QRectF BodyLauncher::boundingRect() const{
  return QRectF(-4000, -4000, 8000, 8000);
}

void BodyLauncher::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setPen(QPen(Qt::red,3));
    QPainterPath p = QPainterPath(start);
    p.lineTo(end);
    painter->drawPath(p);
    QRectF b(0,0,2*10,2*10);
    b.moveTo(start+QPoint(-10,-10));
    painter->drawEllipse(b);
}

void BodyLauncher::grab(QGraphicsSceneMouseEvent *event){
    setVisible(true);
    start = end = event->scenePos();
    update();
}

void BodyLauncher::stretch(QGraphicsSceneMouseEvent *event){
    end = event->scenePos();
    update();
}

void  BodyLauncher::release(QGraphicsSceneMouseEvent *event, QPointF& pos,  QPointF& vel){
    setVisible(false);
    update();
    pos = start;
    vel = (end-start)*.000000025;
}

