#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<landtosystem.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_onbtn_clicked();

    void on_offBtn_clicked();

private:
    Ui::MainWindow *ui;
    LandToSystem l;
        QSqlDatabase db;
};

#endif // MAINWINDOW_H
