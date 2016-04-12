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

    qreal speed;
    QColor color;
    double radius;
    GraphWidget *graph;

    int table_row;
    QList<QTableWidgetItem*> table_items;

public:
    double mass;

    void calculateForces();
    void handleCollision();

    Body(int current_index,QTableWidget *table,GraphWidget *graphWidget);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void setMass(double mass);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    bool advance();

protected:


};

#endif
