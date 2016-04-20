#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QTableWidget>
#include <QTime>
#include "mainwindow.h"
#include <QThread>
#include <QtConcurrent/QtConcurrent>

class Body;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void addBody();
    void removeBody();
    void removeBody(Body *body);

    qreal dt;

    Body getBody(int index);
    QList<Body*> bodies;
    int timerId;
    QTime ElapsedTime;
    void animate(bool a);
    QTableWidget *table;

    bool forceOption_cumulative; //If true velocity force will be cumulative.
    bool forceOption_reverse;    //If true the objects will repel instead of attract.
    bool bodies_collide;         //If true bodies will merge on collision.

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void scaleView(qreal scaleFactor);

private:
 QThreadPool *calc_pool;
};

#endif // GRAPHWIDGET_H
