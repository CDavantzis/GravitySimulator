#include "mygraphicsscene.h"
#include "mygraphicsview.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "qdebug.h"
#include "body.h"

#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>



class forceCalculation : public QRunnable{
private:
    Body *body;
public:
    forceCalculation(Body *body): body(body){}
    virtual void run(){ body->bruteforcePos();}
};



MyGraphicsScene::MyGraphicsScene(QObject* parent, MyGraphicsView*myView): QGraphicsScene(parent), myView(myView){
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(-4000, -4000, 8000, 8000);
    body_launcher = new BodyLauncher();
    this->addItem(body_launcher);
    calc_pool = new QThreadPool(this);
    calc_pool->setMaxThreadCount(8);

}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    switch (event->button()) {
    case Qt::RightButton:
        body_launcher->grab(event);
        break;

    default:
        QGraphicsScene::mousePressEvent(event);
    }
}


void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    mousePos = event->scenePos();
    if (body_launcher->isVisible()){
        body_launcher->stretch(event);
    }
    else{
        QGraphicsScene::mouseMoveEvent(event);
    }
}


void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QPointF pos;
    QPointF vel;
    switch (event->button()) {
    case Qt::RightButton:
        body_launcher->release(event,pos,vel);
        addBody(pos,vel);
        break;
   default:
        QGraphicsScene::mousePressEvent(event);
    }
}

void MyGraphicsScene::calculateForces(){
    foreach (Body *body, bodies){
        body->bruteforcePos();
        //body->attract();
    }
    //calc_pool->waitForDone();
}

void MyGraphicsScene::step(){
    foreach (Body *body, bodies)
        body->step();            //Move To New Postition
}


void MyGraphicsScene::addBody(){
    int cols = table->columnCount();
    int rows = table->rowCount();
    table->insertRow(rows);
    for (int col = 0; col < cols ; ++col)
       table->setItem(rows,col,new QTableWidgetItem("0"));
    Body *body = new Body(this,rows);
    bodies.append(body);
    addItem(body);
}


void MyGraphicsScene::addBody(QPointF pos, QPointF vel){
    int cols = table->columnCount();
    int rows = table->rowCount();
    table->insertRow(rows);
    for (int col = 0; col < cols ; ++col)
       table->setItem(rows,col,new QTableWidgetItem("0"));
    Body *body = new Body(this,rows);
    body->setPos(pos);
    body->vel = vel;
    bodies.append(body);
    addItem(body);
}

void MyGraphicsScene::removeBody(){
    //Remove Body
    int rows = table->rowCount();
    if (rows){
        table->removeRow(rows-1);
        removeItem(bodies.back());
        bodies.pop_back();
    }
}

void MyGraphicsScene::removeBody(Body *body){
    int index = bodies.indexOf(body);
    table->removeRow(index);
    removeItem(bodies[index]);
    bodies.removeAt(index);
    update();
}
