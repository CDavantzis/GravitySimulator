#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QGraphicsItem>

class Launcher : public QGraphicsItem{
private:
    QPointF start;
    QPointF end;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QRectF boundingRect() const Q_DECL_OVERRIDE;

public:
    Launcher();
    void grab(QPointF Pos);
    void stretch(QPointF Pos);
    void release();
};

#endif
