#ifndef STUDENTMEMBER_H
#define STUDENTMEMBER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>
#include"mymodel.h"
namespace Ui {
class StudentMember;
}

class StudentMember : public QWidget
{
    Q_OBJECT

public:
    explicit StudentMember(QWidget *parent = nullptr);
    ~StudentMember();

private slots:
    void on_updateBtn_clicked();

    void on_returnBtn_clicked();

    void on_eneterBtn_clicked();

    void on_checkBtn_clicked();

private:
    Ui::StudentMember *ui;
    QSqlDatabase db ;
    QSqlQuery * query ;
    myModel *tableModel;
};

#endif // STUDENTMEMBER_H
