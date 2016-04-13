#ifndef BODY_H
#define BODY_H
#include <QTableWidget>
#include <QGraphicsItem>
#include <QList>
#include <cmath>

class GraphWidget;

class Body : public QGraphicsItem{
private:
    QPointF newPos;

    GraphWidget *graph;

    int table_row;
    QList<QTableWidgetItem*> table_items;

    qreal mass;   //Object Mass
    qreal radius; //Object Radius

public:
    Body(int current_index,QTableWidget *table,GraphWidget *graphWidget);

    bool advance();

    void calculateForces();
    void handleCollision();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void setMass(qreal mass);

    QColor color;
    QPointF vectVel; //Velocity Vector
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif
