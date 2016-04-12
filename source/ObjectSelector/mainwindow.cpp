#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "body.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->graphicsView->table = ui->tableWidget;

    //connect buttons
    connect(ui->pushButton_add_row, SIGNAL(released()),this, SLOT(add_row()));
    connect(ui->pushButton_remove_row, SIGNAL (released()),this, SLOT(remove_row()));
    connect(ui->pushButton_run, SIGNAL (released()),this, SLOT(Run()));
    connect(ui->pushButton_stop, SIGNAL (released()),this, SLOT(Stop()));
    connect(ui->pushButton_step, SIGNAL (released()),this, SLOT(remove_row()));
    connect(ui->pushButton_randomize, SIGNAL (released()),this->ui->graphicsView, SLOT(shuffle()));

    //connect item edit
    connect(ui->tableWidget->itemDelegate(), &QAbstractItemDelegate::commitData, this, &OnTblItemsCommitData);



}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::Run(){
    //Start animation
    ui->graphicsView->animate(true);
    ui->pushButton_run->setEnabled(false);
    ui->pushButton_stop->setEnabled(true);
    ui->pushButton_step->setEnabled(false);
}

void MainWindow::Stop(){
    //Stop animation
    ui->graphicsView->animate(false);
    ui->pushButton_run->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_step->setEnabled(true);
}


void MainWindow::add_row(){
    //Add body
    int cCol = ui->tableWidget->columnCount();
    int cRow = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(cRow);
    for (int col = 0; col < cCol ; ++col){
       ui->tableWidget->setItem(cRow,col,new QTableWidgetItem("0"));
    }
    ui->graphicsView->addBody(cRow);
}



void MainWindow::remove_row(){
    //Remove Body
    int cRow = ui->tableWidget->rowCount();
    if (cRow != 0){
        int index = cRow - 1;
        ui->tableWidget->removeRow(index);
        ui->graphicsView->removeBody(index);
    }
}






void MainWindow::OnTblItemsCommitData(QWidget* pLineEdit){
    int index_row = ui->tableWidget->currentRow();
    int index_col = ui->tableWidget->currentColumn();

    QString strNewText = reinterpret_cast<QLineEdit*>(pLineEdit)->text();
    int value = strNewText.toInt();

    QGraphicsItem *item = ui->graphicsView->scene()->items()[index_row];

    switch(index_col) {
        case 0 :
            qgraphicsitem_cast<Body *>(item)->setMass(value);
            break;
        case 1 :
             item->setX(value);

              break;
        case 2 :
             item->setY(-value);

              break;
        case 3 :
              break;
   }
   ui->graphicsView->scene()->update();

}



void MainWindow::on_lineEdit_dt_textChanged(const QString &arg1){
    ui->graphicsView->dt = 1 * pow(10, arg1.toInt());
}

void MainWindow::on_checkBox_forceOption_cumulative_toggled(bool checked){
    //If true velocity force will be cumulative.
    ui->graphicsView->forceOption_cumulative = checked;
}

void MainWindow::on_checkBox_forceOption_reverse_toggled(bool checked){
    //If true the objects will repel instead of attract.
    ui->graphicsView->forceOption_reverse = checked;
}
