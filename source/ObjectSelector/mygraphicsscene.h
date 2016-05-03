#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

class Body;
class MyGraphicsView;
class Launcher;

class MyGraphicsScene : public QGraphicsScene{
public:
    MyGraphicsScene(QObject * p = NULL);

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event)   Q_DECL_OVERRIDE;
   void mouseMoveEvent(QGraphicsSceneMouseEvent* event)    Q_DECL_OVERRIDE;
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
   Launcher *launcher;
};

#endif
