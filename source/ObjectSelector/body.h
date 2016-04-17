#ifndef BODY_H
#define BODY_H
#include <QTableWidget>
#include <QGraphicsItem>
#include <QList>
#include <cmath>
#include <QTime>

class GraphWidget;
class blank;
class Body : public QGraphicsItem{
private:
    int index;
    QPointF newPos;

    GraphWidget *graph;
    QList<QTableWidgetItem*> table_items;

    qreal mass;   //Object Mass
    qreal radius; //Object Radius


    QPointF dragStartPos;
    QPointF dragEndPos;
    QTime   dragTime;

    bool destroy_on_next_step;

    void collideWith(Body *other);
public:
    Body(GraphWidget *graphWidget,int index);

    void step(); //Move to newPos

    void calculateForces();
    void handleCollision();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void setMass(qreal mass);

    QColor color;
    QPointF vectVel; //Velocity Vector
    QRectF boundingRect() const Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif
