#ifndef MANAGERLOGIN_H
#define MANAGERLOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include"mymodel.h"


//#include<QDialog>
//#include <QLayout>
//#include<QHBoxLayout>
//#include<QVBoxLayout>
//#include<QLineEdit>
//#include<QPushButton>
//#include<QLabel>

namespace Ui {
class ManagerLogin;
}

class ManagerLogin : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerLogin(QWidget *parent = nullptr);
    ~ManagerLogin();

private slots:
    void on_addBtn_clicked();
    void on_deleteBtn_clicked();
    void on_uptateBtn_clicked();
    void on_selectBtn_clicked();
    void on_returnBtn_clicked();

    void on_pushButton_clicked();
//    void on_enterBttootn_clicked();
    void on_deletePushButton_clicked();

//signals:
//    void add();

    void on_seletnBtn_clicked();

    void on_UPdataBtn_clicked();

private:
    Ui::ManagerLogin *ui;
    QSqlDatabase db ;
    QSqlQuery * query ;
    myModel *tableModel;
    QTimer * timer;


//    QLabel * idLabel;
//    QLabel * Id;
//    QLabel * nameLabel ;
//    QLabel * name ;



};

#endif // MANAGERLOGIN_H
