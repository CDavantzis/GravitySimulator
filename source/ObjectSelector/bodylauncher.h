#ifndef BODYLAUNCHER_H
#define BODYLAUNCHER_H
#include <QTableWidget>
#include <QGraphicsItem>
#include <QList>
#include <cmath>
#include <QTime>
#include <QGraphicsSceneMouseEvent>

class BodyLauncher : public QGraphicsItem{
private:
    QPointF start;
    QPointF end;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QRectF boundingRect() const Q_DECL_OVERRIDE;

public:
    BodyLauncher();
    void grab(QGraphicsSceneMouseEvent *event);
    void stretch(QGraphicsSceneMouseEvent *event);
    void release(QGraphicsSceneMouseEvent *event, QPointF& pos,  QPointF& vel);
};

#endif
