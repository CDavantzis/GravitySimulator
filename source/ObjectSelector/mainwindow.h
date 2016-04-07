#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QTimer *timer;
    ~MainWindow();
    test();
public slots:
    void Run();
    void Stop();
    void update_table();

private slots:
    void add_row();
    void remove_row();
    void OnTblItemsCommitData(QWidget* pLineEdit);


private:
    Ui::MainWindow *ui;
    QTableWidget* m_pTableWidget;
    QStringList m_TableHeader;
    QGraphicsScene *scene;



};

#endif // MAINWINDOW_H
