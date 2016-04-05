#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "planet.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>


namespace SCENE{
    const int x = -1000;
    const int y = -1000;
    const int w = 2000;
    const int h = 2000;

    //draw horizontal and vertical line grid
    void draw_grid(QGraphicsScene *scene){
        scene->addLine(0,scene->sceneRect().top(),0,scene->sceneRect().bottom(),QPen(QBrush(Qt::white),2));
        scene->addLine(scene->sceneRect().left(),0,scene->sceneRect().right(),0,QPen(QBrush(Qt::white),2));
    }
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
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    SCENE::draw_grid(scene);

    //bind buttons to fuctions
    connect(ui->pushButton_add_row, SIGNAL(released()),this, SLOT(add_row()));
    connect(ui->pushButton_remove_row, SIGNAL (released()),this, SLOT(remove_row()));
    connect(ui->pushButton_run, SIGNAL (released()),this, SLOT(Run()));
    connect(ui->pushButton_stop, SIGNAL (released()),this, SLOT(Stop()));
    connect(ui->pushButton_step, SIGNAL (released()),this, SLOT(remove_row()));
    connect(ui->pushButton_update, SIGNAL (released()),this, SLOT(update()));

}

MainWindow::~MainWindow(){
    delete ui;
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
       ui->tableWidget->setItem(index,col,new QTableWidgetItem(""));
    }
}

void MainWindow::remove_row(){
    //remove row from object table
    int current_row = ui->tableWidget->currentRow();
    if (current_row == -1){
        ui->tableWidget->removeRow(ui->tableWidget->rowCount());}
    else{
        ui->tableWidget->removeRow(current_row);}
}

void MainWindow::Run(){
    int dt = ui->lineEdit_dt->text().toInt();
    timer->start(dt);
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

void MainWindow::update(){
    qDebug()<< "clicked";

    //scene->clear();
    int row_count = ui->tableWidget->rowCount()-1;
    int col_count = ui->tableWidget->columnCount()-1;

    for (int row = 0; row < row_count ; ++row)
    {
        QString name =  ui->tableWidget->item(row,0)->text();
        int planet_values[col_count];
        for (int col = 1; col < col_count ; ++col){
            planet_values[col-1] = ui->tableWidget->item(row,col)->text();
        }

       // int y = ui->tableWidget->item(i,4)->text().toInt();
       // Planet *planet = new Planet(Qt::white);
       // planet->setPos(x,y);
       // scene->addItem(planet);
    }
}


