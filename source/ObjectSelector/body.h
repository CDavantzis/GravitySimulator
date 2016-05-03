#ifndef BODY_H
#define BODY_H
#include <QTableWidget>
#include <QGraphicsItem>
#include <QList>
#include <cmath>
#include <QTime>

class MyGraphicsView;

class Body : public QGraphicsItem{
private:
    QPointF newPos;
    QList<QTableWidgetItem*> column;

    qreal mass;
    qreal radius;
    bool  exist;

    void collide(Body *other); //Collide this with other;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void updateTable();

public:
    static int  dT;
    static bool canCollide;
    static QTableWidget *table;
    static QList<Body*> list;
    static MyGraphicsView *view;
    static void push_back();
    static void push_back(QPointF pos, QPointF vel);
    static void pop_back();
    static void step();

    Body();
    QRectF  boundingRect() const Q_DECL_OVERRIDE;
    QPointF calcPosChangeFrom(Body *other);
    QPointF vel;  //Body velocity (vector);

    void setMass(qreal mass);
    void setRadius(qreal radius);
    void getNewPos();
    void updatePos();
    void remove();


};


#endif
