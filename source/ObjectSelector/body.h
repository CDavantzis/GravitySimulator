#ifndef BODY_H
#define BODY_H
#include <QTableWidget>
#include <QGraphicsItem>
#include <QList>
#include <cmath>

class Body : public QGraphicsItem{
private:
    qreal speed;
    QColor color;
    double mass;
    double radius;

    int table_row;
    QList<QTableWidgetItem*> table_items;

public:
    Body(int current_index,QTableWidget *table);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void setRadius(double radius);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

protected:
    void advance(int step) Q_DECL_OVERRIDE;


};

#endif
