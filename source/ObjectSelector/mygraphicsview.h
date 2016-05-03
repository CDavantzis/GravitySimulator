#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QTime>
#include <QFuture>
#include <QKeyEvent>
#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView{

private:
    int timerId;
    QTime dT;
    void zoomIn();
    void zoomOut();

public:
    MyGraphicsView(QWidget *parent = 0);
    void animate(bool a);

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
