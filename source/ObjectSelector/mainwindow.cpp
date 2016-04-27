#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->graphicsView->setupTable(ui->tableWidget);
    //set values to initial .ui conditions
    Body::canCollide =  ui->checkBox_bodies_collide->isChecked();

    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing,ui->checkBox_antialiasing->checkState());
    ui->statusBar->showMessage(tr("Ready"));
    //Make Connections
    connect(ui->pushButton_randomize, SIGNAL (released()),this->ui->graphicsView, SLOT(shuffle()));
    connect(ui->tableWidget->itemDelegate(), &QAbstractItemDelegate::commitData, this, &OnTblItemsCommitData);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::OnTblItemsCommitData(QWidget* pLineEdit){
    int row = ui->tableWidget->currentRow();
    int col = ui->tableWidget->currentColumn();
    double value = (reinterpret_cast<QLineEdit*>(pLineEdit)->text()).toDouble();
    Body *body = ui->graphicsView->myScene->bodies[row];
    switch(col) {
        case 0:
            body->setMass(value);
            break;
        case 1:
            body->setX(value);
            break;
        case 2:
            body->setY(-value);
            break;
        case 3:
            body->vel.setX(value);
            break;
        case 4:
            body->vel.setY(-value);
            break;
    }
     ui->graphicsView->scene()->update();
}

//lineEdit Slots

//Start animation
void MainWindow::on_pushButton_run_clicked(){
    ui->graphicsView->animate(true);
    ui->pushButton_run->setEnabled(false);
    ui->pushButton_stop->setEnabled(true);
}
void MainWindow::on_pushButton_stop_clicked(){
    //Stop animation
    ui->graphicsView->animate(false);
    ui->pushButton_run->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
}

void MainWindow::on_pushButton_add_row_clicked(){
    ui->graphicsView->myScene->addBody();
}
void MainWindow::on_pushButton_remove_row_clicked(){
    ui->graphicsView->myScene->removeBody();
}

//checkBox Slots
void MainWindow::on_checkBox_bodies_collide_toggled(bool checked){
    Body::canCollide = checked;
}
void MainWindow::on_checkBox_antialiasing_toggled(bool checked){
    //If true the graphicsview will render in high quality.
    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing, checked);
}


