#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>

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
    QGraphicsScene *scene;

private slots:
    void OnTblItemsCommitData(QWidget* pLineEdit);

    //lineEdit Slots
    void on_lineEdit_dt_textChanged(const QString &arg1);

    //pushButton Slots
    void on_pushButton_run_clicked();
    void on_pushButton_stop_clicked();
    void on_pushButton_add_row_clicked();
    void on_pushButton_remove_row_clicked();

    //checkBox Slots
    void on_checkBox_forceOption_cumulative_toggled(bool checked);
    void on_checkBox_forceOption_reverse_toggled(bool checked);
    void on_checkBox_antialiasing_toggled(bool checked);
    void on_checkBox_bodies_collide_toggled(bool checked);
};

#endif // MAINWINDOW_H
