#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "body.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <vector>





MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);


        //bind buttons to fuctions
        connect(ui->pushButton_add_row, SIGNAL(released()),this, SLOT(add_row()));
        connect(ui->pushButton_remove_row, SIGNAL (released()),this, SLOT(remove_row()));
        connect(ui->pushButton_run, SIGNAL (released()),this, SLOT(Run()));
        connect(ui->pushButton_stop, SIGNAL (released()),this, SLOT(Stop()));
        connect(ui->pushButton_step, SIGNAL (released()),this, SLOT(remove_row()));
        connect(ui->pushButton_update, SIGNAL (released()),this, SLOT(update()));
        connect(ui->tableWidget->itemDelegate(), &QAbstractItemDelegate::commitData, this, &OnTblItemsCommitData);
        timer = new QTimer(this);



}

MainWindow::~MainWindow(){
    delete ui;
}

MainWindow::test(){

}



void MainWindow::OnTblItemsCommitData(QWidget* pLineEdit){
    int index_row = ui->tableWidget->currentRow();
    int index_col = ui->tableWidget->currentColumn();

    QString strNewText = reinterpret_cast<QLineEdit*>(pLineEdit)->text();
    int value = strNewText.toInt();

    QGraphicsItem *item = ui->graphicsView->scene()->items()[index_row];

    switch(index_col) {
        case 0 : qDebug() << '1';
            break;
        case 1 :
              qgraphicsitem_cast<Body *>(item)->setRadius(value);
              break;
        case 2 :
             item->setX(value);
              break;
        case 3 :
              item->setY(-value);
              break;
   }
   ui->graphicsView->scene()->update();

}


void MainWindow::add_row(){
    int cCol = ui->tableWidget->columnCount();
    int cRow = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(cRow);
    for (int col = 0; col < cCol ; ++col){
       ui->tableWidget->setItem(cRow,col,new QTableWidgetItem("0"));
    }
    ui->graphicsView->addBody(cRow,ui->tableWidget);
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
    ui->tableWidget->removeRow(index);
    ui->graphicsView->removeBody(index);
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


}
