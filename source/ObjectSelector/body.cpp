#include "body.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>




Body::Body(int current_index, GraphWidget *graphWidget,QTableWidget *table):graph(graphWidget),color(Qt::white){
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setRadius(30);
    setZValue(-1);
    setPos(0,0);

    int column_count = table->columnCount();
    for (int i = 0; i < column_count; i++){
        this->table_items.append(table->item(current_index,i));
    }
}

void  Body::setRadius(double radius){
    this->radius = radius;
    update();
}



QRectF Body::boundingRect() const{
    return QRectF(-radius-1,-radius-1,2*radius+2,2*radius+2);
}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(QRectF(-radius,-radius,2*radius,2*radius));
}

void Body::advance(int step)
{
    if (!step)
        return;
    //moveBy(1,-1);

    setPos(mapToParent(1, -1));

}



QVariant Body::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange){
        this->table_items[2]->setText(QString::number(pos().x()));
        this->table_items[3]->setText(QString::number(-pos().y()));
    }
    return QGraphicsItem::itemChange(change, value);
}


