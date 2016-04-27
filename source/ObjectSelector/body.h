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
    static int  dT;
    static bool canCollide;

    Body(MyGraphicsScene *myScene,int index);
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    QPointF vel;  //Body velocity (vector);
    void setMass(qreal mass); //Set body mass;

    void getNewPos();           //Use bruteforce for N-Body calculations;
    void moveToNewPos();           //Move body to newPos;

    QPointF calcPosChangeFrom(Body *other);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

};


#endif
