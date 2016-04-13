#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "body.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->graphicsView->table = ui->tableWidget;

    //set values to initial .ui conditions
    ui->graphicsView->forceOption_cumulative = ui->checkBox_forceOption_cumulative->checkState();
    ui->graphicsView->forceOption_reverse = ui->checkBox_forceOption_reverse->checkState();
    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing,ui->checkBox_antialiasing->checkState());
    ui->graphicsView->dt = 1*pow(10,ui->lineEdit_dt->text().toInt());

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
    QGraphicsItem *item = ui->graphicsView->scene()->items()[row];
    if (Body *body = qgraphicsitem_cast<Body *>(item)){
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
                body->vectVel.setX(value);
                break;
            case 4:
                body->vectVel.setY(-value);
                break;
        }
     }
     ui->graphicsView->scene()->update();
}


//lineEdit Slots
void MainWindow::on_lineEdit_dt_textChanged(const QString &arg1){
    ui->graphicsView->dt = 1 * pow(10, arg1.toInt());
}

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
    //Add body
    int cCol = ui->tableWidget->columnCount();
    int cRow = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(cRow);
    for (int col = 0; col < cCol ; ++col){
       ui->tableWidget->setItem(cRow,col,new QTableWidgetItem("0"));
    }
    ui->graphicsView->addBody(cRow);
}
void MainWindow::on_pushButton_remove_row_clicked(){
    //Remove Body
    int cRow = ui->tableWidget->rowCount();
    if (cRow != 0){
        int index = cRow - 1;
        ui->tableWidget->removeRow(index);
        ui->graphicsView->removeBody(index);
    }
}

//checkBox Slots
void MainWindow::on_checkBox_forceOption_cumulative_toggled(bool checked){
    //If true velocity force will be cumulative.
    ui->graphicsView->forceOption_cumulative = checked;
}

void MainWindow::on_checkBox_forceOption_reverse_toggled(bool checked){
    //If true the objects will repel instead of attract.
    ui->graphicsView->forceOption_reverse = checked;
}

void MainWindow::on_checkBox_antialiasing_toggled(bool checked){
    //If true the graphicsview will render in high quality.
    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing, checked);
}



