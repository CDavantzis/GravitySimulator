#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QTime>
#include <QFuture>
#include <QKeyEvent>
#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView{

public:
    MyGraphicsView(QWidget *parent = 0);

    int timerId;
    QTime dT;
    void animate(bool a);

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

};

#endif // GRAPHWIDGET_H
