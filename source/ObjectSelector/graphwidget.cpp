#include "graphwidget.h"
#include "body.h"

#include <math.h>
#include <QKeyEvent>
#include <QDebug>
GraphWidget::GraphWidget(QWidget *parent): QGraphicsView(parent), timerId(0)
{
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setCacheMode(QGraphicsView::CacheBackground);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-1000, -1000, 2000, 2000);
    setScene(scene);
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
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

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    //QList<Planet *> planets;
    //foreach (QGraphicsItem *item, scene()->items()) {
    //    if (Node *node = qgraphicsitem_cast<Node *>(item))
    //        nodes << node;
    //}

   // foreach (Node *node, nodes)
   //     node->calculateForces();

   // bool itemsMoved = false;
   // foreach (Node *node, nodes) {
    //    if (node->advance())
    //        itemsMoved = true;
    //}

   // if (!itemsMoved) {
   //     killTimer(timerId);
   //     timerId = 0;
   // }
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
   // foreach (QGraphicsItem *item, scene()->items()) {
    //    if (qgraphicsitem_cast<Node *>(item))
     //       item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
    //}
}

void GraphWidget::zoomIn(){
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut(){

    scaleView(1 / qreal(1.2));
}


void GraphWidget::addBody(int index,QTableWidget *table){
    Body *planet = new Body(index,this,table);
    scene()->addItem(planet);
}

void GraphWidget::removeBody(int index){
    scene()->removeItem(scene()->items()[index]);
}


