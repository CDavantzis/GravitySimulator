#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "body.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <vector>
#include <cmath>

namespace SCENE{
    const int x = -2000;
    const int y = -2000;
    const int w = 4000;
    const int h = 4000;

    //draw horizontal and vertical line grid
    void reset(QGraphicsScene *scene){
        scene->clear();
        scene->addLine(0,scene->sceneRect().top(),0,scene->sceneRect().bottom(),QPen(QBrush(Qt::white),2));
        scene->addLine(scene->sceneRect().left(),0,scene->sceneRect().right(),0,QPen(QBrush(Qt::white),2));
    }
    std::vector<Body*> bodies;

}



MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);


    //Configure QGraphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black));
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    //Configure QGraphicsScene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(SCENE::x,SCENE::y,SCENE::w,SCENE::h);
    //scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    SCENE::reset(scene);

    //bind buttons to fuctions
    connect(ui->pushButton_add_row, SIGNAL(released()),this, SLOT(add_row()));
    connect(ui->pushButton_remove_row, SIGNAL (released()),this, SLOT(remove_row()));
    connect(ui->pushButton_run, SIGNAL (released()),this, SLOT(Run()));
    connect(ui->pushButton_stop, SIGNAL (released()),this, SLOT(Stop()));
    connect(ui->pushButton_step, SIGNAL (released()),this, SLOT(remove_row()));
    connect(ui->pushButton_update, SIGNAL (released()),this, SLOT(update()));



    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(timer, SIGNAL(timeout()), this, SLOT(update_table()));
    connect(ui->tableWidget->itemDelegate(), &QAbstractItemDelegate::commitData, this, &OnTblItemsCommitData);

}

MainWindow::~MainWindow(){
    delete ui;
}



void MainWindow::OnTblItemsCommitData(QWidget* pLineEdit)
{
    qDebug() << "HERE!";
    QString strNewText = reinterpret_cast<QLineEdit*>(pLineEdit)->text();
    int value = strNewText.toInt();
    int nRow = ui->tableWidget->currentRow();
    int nCol = ui->tableWidget->currentColumn();
    switch(nCol) {
        case 0 : qDebug() << '1';
            break;
        case 1 :
            SCENE::bodies[nRow]->setRadius(value);
            break;
        case 2 :
            SCENE::bodies[nRow]->setX(value);
            break;
        case 3 :
            SCENE::bodies[nRow]->setY(-value);
            break;
    }
    scene->update();
}


void MainWindow::add_row(){
    //add row to object table
    int current_row = ui->tableWidget->currentRow();
    int index = 0;
    if (current_row == -1){
        index = ui->tableWidget->rowCount();
    }
    else{
        index = current_row+1;
     }
    ui->tableWidget->insertRow(index);
    int col_count = ui->tableWidget->columnCount();
    for (int col = 0; col < col_count ; ++col){
       ui->tableWidget->setItem(index,col,new QTableWidgetItem("0"));
    }
    Body *body = new Body(ui->tableWidget,index);
    scene->addItem(body);
    SCENE::bodies.insert(SCENE::bodies.begin()+index, body);

}

void MainWindow::remove_row(){
    //remove row from object table
    int index = ui->tableWidget->currentRow();
    if (index == -1){
        index = ui->tableWidget->rowCount()-1;
         if (index == -1){
             return;
         }
    }
    scene->removeItem(SCENE::bodies[index]);
    SCENE::bodies.erase(SCENE::bodies.begin()+index);
    ui->tableWidget->removeRow(index);



}

void MainWindow::Run(){
    timer->start(10);
    ui->pushButton_run->setEnabled(false);
    ui->pushButton_stop->setEnabled(true);
    ui->pushButton_step->setEnabled(false);
}

void MainWindow::Stop(){
    timer->stop();
    ui->pushButton_run->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_step->setEnabled(true);
}

void MainWindow::update_table(){
    //qDebug() <<   (qobject_cast<QTimer*>(sender())->interval()) % 1000;
    int rows = ui->tableWidget->rowCount();
    for (int i = 0; i < rows; i++){
        QPointF position =  SCENE::bodies[i]->pos();
        QString x =  QString::number(position.x());
        QString y =  QString::number(-position.y());
        ui->tableWidget->item(i,2)->setText(x);
        ui->tableWidget->item(i,3)->setText(y);

    }




}
