#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QtWidgets/QLineEdit>

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

private slots:

    void on_actionExportCSV_triggered();
    void on_actionImportCSV_triggered();

    void on_checkBox_bodies_collide_toggled(bool checked);

    void on_pushButton_run_clicked();
    void on_pushButton_stop_clicked();
    void on_pushButton_add_row_clicked();
    void on_pushButton_remove_row_clicked();
    void on_pushButton_randomize_clicked();

    void on_tableItemsCommitData(QWidget* pLineEdit);


};

#endif // MAINWINDOW_H
