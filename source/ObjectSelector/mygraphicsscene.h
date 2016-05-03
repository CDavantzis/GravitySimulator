#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

#include "bodylauncher.h"

class Body;
class MyGraphicsView;

class MyGraphicsScene : public QGraphicsScene{
public:
    MyGraphicsScene( QObject * p = NULL, MyGraphicsView*myView = NULL);
    MyGraphicsView *myView;

    void step();
    QPointF mousePos;

public slots:
    void addBody();
    void addBody(QPointF pos, QPointF vel);

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event)   Q_DECL_OVERRIDE;
   void mouseMoveEvent(QGraphicsSceneMouseEvent* event)    Q_DECL_OVERRIDE;
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
   BodyLauncher *body_launcher;
     QThreadPool *calc_pool;
};

#endif
