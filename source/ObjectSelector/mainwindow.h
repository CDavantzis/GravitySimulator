#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets/QLineEdit>
#include "mygraphicsscene.h"
#include "body.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyGraphicsScene *scene;

private slots:
    void OnTblItemsCommitData(QWidget* pLineEdit);

    //pushButton Slots
    void on_pushButton_run_clicked();
    void on_pushButton_stop_clicked();
    void on_pushButton_add_row_clicked();
    void on_pushButton_remove_row_clicked();

    //checkBox Slots
    void on_checkBox_antialiasing_toggled(bool checked);
    void on_checkBox_bodies_collide_toggled(bool checked);
};

#endif // MAINWINDOW_H
