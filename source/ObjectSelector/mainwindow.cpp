#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    //bind buttons to fuctions
    connect(ui->pushButton_add_row, SIGNAL(released()),this, SLOT(add_row()));
    connect(ui->pushButton_remove_row, SIGNAL (released()),this, SLOT(remove_row()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::add_row(){
    //add row to object table
    int current_row = ui->tableWidget->currentRow();
    if (current_row == -1){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());}
    else{
        ui->tableWidget->insertRow(current_row+1);}
}

void MainWindow::remove_row(){
    //remove row from object table
    int current_row = ui->tableWidget->currentRow();
    if (current_row == -1){
        ui->tableWidget->removeRow(ui->tableWidget->rowCount());}
    else{
        ui->tableWidget->removeRow(current_row);}
}

