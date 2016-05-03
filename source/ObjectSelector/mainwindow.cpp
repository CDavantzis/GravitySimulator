#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "body.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    Body::table = ui->tableWidget;
    Body::view  = ui->graphicsView;
    Body::canCollide =  ui->checkBox_bodies_collide->isChecked();
    connect(ui->tableWidget->itemDelegate(), &QAbstractItemDelegate::commitData, this, &on_tableItemsCommitData);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_tableItemsCommitData(QWidget* pLineEdit){
    double value = (reinterpret_cast<QLineEdit*>(pLineEdit)->text()).toDouble();
    int row = ui->tableWidget->currentRow();
    int col = ui->tableWidget->currentColumn();
    Body *body = Body::list[row];
    switch(col) {
        case 0:
            body->setMass(value);
            break;
        case 1:
            body->setRadius(value);
            break;
        case 2:
            body->setX(value);
            break;
        case 3:
            body->setY(-value);
            break;
        case 4:
            body->vel.setX(value);
            break;
        case 5:
            body->vel.setY(-value);
            break;
    }
}

void MainWindow::on_pushButton_run_clicked(){
    //Start animation
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
    Body::push_back();
}
void MainWindow::on_pushButton_remove_row_clicked(){
    Body::pop_back();
}
void MainWindow::on_checkBox_bodies_collide_toggled(bool checked){
    Body::canCollide = checked;
}
void MainWindow::on_pushButton_randomize_clicked(){
    Body::shuffle();
}

void MainWindow::on_actionExportTXT_triggered(){
    //Export TXT file from Table
    QList<QString> list;
    QFileDialog Dialog;
    Dialog.setDefaultSuffix("csv");
    QString filename = Dialog.getSaveFileName(this, tr("SaveFile"), "C://", "Project File(*.txt)");
    QFile f(filename);
    if (!filename.isEmpty() && (f.open(QFile::WriteOnly | QFile::Truncate)))    {
        QTextStream out(&f);
        out << ui->tableWidget->rowCount() << "\n";
        out << ui->tableWidget->columnCount() << "\n";
        for( int r = 0; r < ui->tableWidget->rowCount(); ++r ){
            for( int c = 0; c < ui->tableWidget->columnCount(); ++c ){
                out << ui->tableWidget->item(r,c)->text() << "\n";
            }
        }
        f.close();
    }
}



void MainWindow::on_actionImportTXT_triggered(){
    //Import TXT file into Table
    QFileDialog Dialog;
    QString filename = Dialog.getOpenFileName(this, tr("Open File"), "C://", "Project File (*.txt)");
    QFile f(filename);
    QTextStream out(&f);
    if (!filename.isEmpty() && (f.open(QFile::ReadOnly | QFile::Truncate)))    {
        while(Body::list.length()>0){
            Body::pop_back();
        }
        int rows = f.readLine().trimmed().toInt();
        int cols = f.readLine().trimmed().toInt();
        for( int r = 0; r < rows; ++r ){
            QList<QString> body_data;
            for( int c = 0; c < cols; ++c ){
                body_data.append(f.readLine().trimmed());
            }
            Body::push_back(body_data);
        }
        f.close();
    }
}
