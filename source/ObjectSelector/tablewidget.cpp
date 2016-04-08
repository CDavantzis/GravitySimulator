#include "body.h"
#include "graphwidget.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

Body::Body(int current_index, QTableWidget *table):color(Qt::white){
    int column_count = table->columnCount();
    for (int i = 0; i < column_count; i++){
        table_items.append(table->item(current_index,i));
    }
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setPos(0,0);
    setRadius(30);
}




void  Body::setRadius(double radius){
    this->radius = radius;
    //this->table_items[1]->setText(QString::number(radius));
    update();
}


QRectF Body::boundingRect() const{
    return QRectF(-radius-1,-radius-1,2*radius+2,2*radius+2);
}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(QRectF(-radius,-radius,2*radius,2*radius));
    painter->setPen(Qt::black);
    painter->setFont(QFont("Arial",radius));
    painter->drawText(this->boundingRect(), Qt::AlignCenter, QString::number(table_items[0]->row()+1));
}

QVariant Body::itemChange(GraphicsItemChange change, const QVariant &value){
    //Called when item's state changes
    if (change == ItemPositionChange){
        //Update table values with changed position
        this->table_items[2]->setText(QString::number(pos().x()));
        this->table_items[3]->setText(QString::number(-pos().y()));
    }
    return QGraphicsItem::itemChange(change, value);
}


void Body::advance(int step)
{
    if (!step)
        return;
    //moveBy(1,-1);

    setPos(mapToParent(1, -1));

}



