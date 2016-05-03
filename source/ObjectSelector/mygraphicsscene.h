#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class Launcher;

class MyGraphicsScene : public QGraphicsScene{

private:
   Launcher *launcher;

public:
    MyGraphicsScene(QObject * p = NULL);

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event)   Q_DECL_OVERRIDE;
   void mouseMoveEvent(QGraphicsSceneMouseEvent* event)    Q_DECL_OVERRIDE;
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

};

#endif
