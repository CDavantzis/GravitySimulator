#include "glwidget.h"

#include <QPainter>
#include <QTimer>
#include <QPaintEvent>
#include <QOpenGLFunctions>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    elapsed = 0;
    setAutoFillBackground(false);
}


void GLWidget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    //QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    //f->glClearColor(1,0,0,1);

    QPainter painter;
    painter.begin(this);


    painter.setRenderHint(QPainter::Antialiasing);

    clear(&painter, event);
    painter.setBrush(QBrush(Qt::white));

    painter.drawEllipse(elapsed/10,10,10,10);

    painter.end();
}


void GLWidget::clear(QPainter *painter, QPaintEvent *event)
{
    painter->fillRect(event->rect(), QBrush(Qt::black));
}


