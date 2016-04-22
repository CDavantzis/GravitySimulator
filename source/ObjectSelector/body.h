#ifndef BODY_H
#define BODY_H
#include <QTableWidget>
#include <QGraphicsItem>
#include <QList>
#include <cmath>
#include <QTime>

class MyGraphicsScene;
class Body : public QGraphicsItem{
private:
    int index;
    QPointF newPos;

    MyGraphicsScene *myScene;
    QList<QTableWidgetItem*> table_items;

    qreal mass;   //Body mass
    qreal radius; //Body radius

    void collide(Body *other); //Collide this with other;
    bool exist;

public:
    static bool canCollide;
    static int  dT;

    Body(MyGraphicsScene *myScene,int index);
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    QPointF vel;  //Body velocity (vector);
    QColor color; //Body color;

    void step();                 //Move body to newPos;
    void setMass(qreal mass);    //Set body mass;
    void bruteforcePos();        //Use bruteforce for N-Body calculations;
    void barneshutPos();         //Use Barnes–Hut for N-Body calculations;
    void particlemeshPos();      //Use particle mesh for N-Body calculations;

    QPointF forcesFrom(Body *other);
    QPointF forcesFromMouse();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

};

#endif
