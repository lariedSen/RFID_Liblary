#ifndef OTHERMEMBER_H
#define OTHERMEMBER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>
#include"mymodel.h"
namespace Ui {
class OtherMember;
}

class OtherMember : public QWidget
{
    Q_OBJECT

public:
    explicit OtherMember(QWidget *parent = nullptr);
    ~OtherMember();

private slots:
    void on_returnBtn_clicked();

    void on_enterBtn_clicked();

private:
    Ui::OtherMember *ui;
    QSqlDatabase db ;
      myModel *tableModel;

};

#endif // OTHERMEMBER_H
