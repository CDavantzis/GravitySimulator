#ifndef BODY_H
#define BODY_H

#include <cmath>
#include <QPainter>
#include <QGraphicsItem>
#include <QTableWidget>

class MyGraphicsView;

class Body : public QGraphicsItem{
private:
    QPointF newPos;
    QList<QTableWidgetItem*> column;
    qreal mass;
    qreal radius;
    bool  exist;
    void collide(Body *other);
    void updateTable();
    QPointF getNewPos();
    void updatePos();
    void remove();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

public:
    Body();
    QRectF  boundingRect() const Q_DECL_OVERRIDE;
    QPointF calcPosChangeFrom(Body *other);
    QPointF vel;
    void setMass(qreal mass);
    void setRadius(qreal radius);

    static int  dT;
    static bool canCollide;
    static QTableWidget *table;
    static QList<Body*> list;
    static MyGraphicsView *view;
    static void push_back();
    static void push_back(QPointF pos, QPointF vel);
    static void pop_back();
    static void step();
};

#endif
