#ifndef BODY_H
#define BODY_H
#include <QTableWidget>
#include <QGraphicsItem>
#include <vector>
#include <cmath>
class Body : public QGraphicsItem{
private:
    qreal speed;
    QColor color;
    double mass;
    int index;
    double radius;





public:
    Body(double mass, double radius, double x, double y);
    Body(QTableWidget *table,int index);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void setRadius(double radius);

protected:
    void advance(int step) Q_DECL_OVERRIDE;


};

#endif
