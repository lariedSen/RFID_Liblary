#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>

#include"managerlogin.h"
#include"studentmember.h"
#include"othermember.h"
#include<QRegExpValidator>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_returnBtn_clicked();
    void on_enterBtn_clicked();

public:
    void Manager(int id);
    void Student(int id);
    void Other(int id );



//signals:
//    void ManagerSigned();
//    void StudentSigned()  ;
//    void OtherSigned()  ;

private:
    Ui::Login *ui;
    QSqlDatabase db;
    ManagerLogin m;
    StudentMember s;
    OtherMember o;

};

#endif // LOGIN_H
