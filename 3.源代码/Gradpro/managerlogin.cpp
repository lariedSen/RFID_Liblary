#include "managerlogin.h"
#include "ui_managerlogin.h"
#include<QDebug>
#include<QMessageBox>
#include<QTimer>
#include"login.h"
ManagerLogin::ManagerLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerLogin)
{
    ui->setupUi(this);

    tableModel = new myModel(this);
    ui->tableView->setModel(tableModel);
    // 打开数据库文件
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lisen.db");
    db.open();
    tableModel->setQuery("SELECT * FROM PASSWORD");

    //正则表达式限制输入
    QRegExp reg("^[a-zA-Z0-9]+$");
    QValidator*validator = new QRegExpValidator(reg);

    QRegExp regid("^[0-9]+$");
    QValidator*validatorid = new QRegExpValidator(reg);

    //更新
    ui->IDEdit->setValidator(validatorid);
    ui->namelineEdit->setValidator(validator);
    //删除
    ui->deleteEDit->setValidator(validatorid);
    //查找
     ui->seleteLineEDit->setValidator(validatorid);
    //更新
    ui->updataIDeEdit->setValidator(validatorid);
    ui->updataNameEdit->setValidator(validator);
    ui->updataPasseEdit->setValidator(validator);


}

ManagerLogin::~ManagerLogin()
{
    delete ui;
}



void ManagerLogin::on_addBtn_clicked()
{
    QMessageBox::information(this,tr("添加提示"),
                             tr("请输入ID、名字、选择性别、身份"));
    ui->IDEdit->clear();
    ui->namelineEdit->clear();
    tableModel->setQuery("SELECT * FROM PASSWORD");
}

void ManagerLogin::on_deleteBtn_clicked()
{
    QMessageBox::information(this,tr("删除提示"),tr("请输入ID，选择身份"));
    ui->deleteEDit->clear();
    tableModel->setQuery("SELECT * FROM PASSWORD");
}

void ManagerLogin::on_uptateBtn_clicked()
{
    tableModel->setQuery("SELECT * FROM PASSWORD");
    ui->updataIDeEdit->clear();
    ui->updataNameEdit->clear();
    ui->updataPasseEdit->clear();

}

void ManagerLogin::on_selectBtn_clicked()
{
    tableModel->setQuery("SELECT * FROM PASSWORD");
     ui->seleteLineEDit->clear();


}

void ManagerLogin::on_returnBtn_clicked()
{
        Login* l = new Login();
        l->show();
        this->close();
        db.close();
}


//点击添加那妞槽函数
void ManagerLogin::on_pushButton_clicked()
{
    //获取数据
    int id = ui->IDEdit->text().toInt();
    QString name = ui->namelineEdit->text();
     QString sex = ui->sexcomboBox->currentText();
    QString pers = ui->personComboBox->currentText();

    QSqlQuery query(db);

    /*
    0: mamager
    1: student
    2: member
*/
    switch (ui->personComboBox->currentIndex()) {
    case 0 :
        {
            QString addsql =QString("insert into MANAGER(ID,NAME,SEX,PERSONNEL,POST) "
                                    "values(%1,'%2','%3','%4','--')")
                    .arg(id)
                    .arg(name)
                    .arg(sex)
                    .arg(pers);
            QString passsql =QString("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) "
                                    "values(%1,'%2','%3','%4')")
                    .arg(id)
                    .arg(id)
                    .arg(name)
                    .arg(pers);
                bool isok =  query.exec(addsql);
                bool isok1 =  query.exec(passsql);
                qDebug() << isok << isok1;
                if(!isok||!isok1)
                {
                    QMessageBox::information(this,tr("提示"),
                                             tr("add error"));
                }
                else {
                    tableModel->setQuery("SELECT * FROM MANAGER");
                }


        }
        break;
    case 1 :
        {
            QString addsql =QString("insert into STUDENT(ID,NAME,SEX,PERSONNEL) "
                                    "values(%1,'%2','%3','%4')")
                    .arg(id)
                    .arg(name)
                    .arg(sex)
                    .arg(pers);
            QString passsql =QString("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) "
                                    "values(%1,'%2','%3','%4')")
                    .arg(id)
                    .arg(id)
                    .arg(name)
                    .arg(pers);
           bool isok =  query.exec(addsql);
            bool isok1 =  query.exec(passsql);
           qDebug() << isok << isok1;
           if(!isok||!isok1)
           {
               QMessageBox::information(this,tr("提示"),
                                        tr("add error"));
           }
           else {
               tableModel->setQuery("SELECT * FROM STUDENT");
           }
        }
        break;
    case 2 :
        {
            QString addsql =QString("insert into MEMBER(ID,NAME,SEX,PERSONNEL) "
                                    "values(%1,'%2','%3','%4')")
                    .arg(id)
                    .arg(name)
                    .arg(sex)
                    .arg(pers);
            QString passsql =QString("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) "
                                    "values(%1,'%2','%3','%4')")
                    .arg(id)
                    .arg(id)
                    .arg(name)
                    .arg(pers);
           bool isok =  query.exec(addsql);
            bool isok1 =  query.exec(passsql);
           qDebug() << isok << isok1;
           if(!isok||!isok1)
           {
               QMessageBox::information(this,tr("提示"),
                                        tr("add error"));
           }
           else {
               tableModel->setQuery("SELECT * FROM MEMBER");
           }

        }
        break;
    default:
        {
            qDebug()<<"no this man"<<db.lastError().text();
            exit(0);
        }
        break;
    }

}

////查看槽函数
//void ManagerLogin::on_enterBttootn_clicked()
//{

//}

//删除槽函数
void ManagerLogin::on_deletePushButton_clicked()
{


    QSqlQuery query(db);
    switch (ui->deleteComboBox->currentIndex()) {
    case 0 :
        {
            QString deletesql = QString("delete from MANAGER where id = %1")
                .arg(ui->deleteEDit->text().toInt());
            qDebug() << deletesql;
             bool isok =  query.exec(deletesql);

            QString deletepass = QString("delete from PASSWORD where id = %1")
                .arg(ui->deleteEDit->text().toInt());
            qDebug() << deletesql;
             bool isok1 =  query.exec(deletepass);
            qDebug() << isok << isok1;
            if(!isok||!isok1)
            {
                QMessageBox::information(this,tr("提示"),
                                         tr("delete error : meybe no this gay"));
            }
            else {
                tableModel->setQuery("SELECT * FROM MANAGER");
            }
        }
        break;
    case 1 :
        {
            QString deletesql = QString("delete from STUDENT where id = %1")
                .arg(ui->deleteEDit->text().toInt());
            qDebug() << deletesql;
             bool isok =  query.exec(deletesql);

            QString deletepass = QString("delete from PASSWORD where id = %1")
                .arg(ui->deleteEDit->text().toInt());
            qDebug() << deletesql;
             bool isok1 =  query.exec(deletepass);
            qDebug() << isok << isok1;
            if(!isok||!isok1)
            {
                QMessageBox::information(this,tr("提示"),
                                         tr("delete error : meybe no this gay"));
            }
            else {
                tableModel->setQuery("SELECT * FROM STUDENT");
            }
        }
        break;
    case 2 :
        {
            QString deletesql = QString("delete from MEMBER where id = %1")
                .arg(ui->deleteEDit->text().toInt());
            qDebug() << deletesql;
             bool isok =  query.exec(deletesql);

            QString deletepass = QString("delete from PASSWORD where id = %1")
                .arg(ui->deleteEDit->text().toInt());
            qDebug() << deletesql;
             bool isok1 =  query.exec(deletepass);
            qDebug() << isok << isok1;
            if(!isok||!isok1)
            {
                QMessageBox::information(this,tr("提示"),
                                         tr("delete error : meybe no this gay"));
            }
            else {
                tableModel->setQuery("SELECT * FROM MEMBER");
            }

        }
        break;
    default:
        {
            qDebug()<<"no this man"<<db.lastError().text();
            exit(0);
        }
        break;
    }
//    tableModel->setQuery("SELECT * FROM PASSWORD");

}

//根据信息查找
void ManagerLogin::on_seletnBtn_clicked()
{
    QSqlQuery query(db);
    query.exec("select * from PASSWORD");

    while(query.next())
    {
        int id = query.value(0).toInt();
        if(id ==ui->seleteLineEDit->text().toInt() )
        {
            QString person = query.value("PERSONNEL").toString();
            if(person == "manager")
            {
                tableModel->setQuery("SELECT * FROM MANAGER");
                break;
            }
            else if(person == "student")
            {
                 tableModel->setQuery("SELECT * FROM STUDENT");
                 break;
            }
            else if (person == "member")
            {
                tableModel->setQuery("SELECT * FROM MEMBER");
                 break;
            }
            else {
                qDebug()<<"error";
                QMessageBox::information(this,tr("提示"),
                                           tr("error: meybe no this gay"));
            }
        }

    }
}

void ManagerLogin::on_UPdataBtn_clicked()
{
    QSqlQuery query(db);
    query.exec("select * from PASSWORD");
    while(query.next())
    {
        int id = query.value(0).toInt();
        QString person = query.value("PERSONNEL").toString();
        if(id ==ui->updataIDeEdit->text().toInt() )
        {
            QString updatasql = QString("update PASSWORD "
                                        "set PASS = '%1',NAME = '%2',PERSONNEL = '%3'"
                                        "where ID = %4 ")
                    .arg(ui->updataPasseEdit->text())
                    .arg(ui->updataNameEdit->text())
                    .arg(person)
                    .arg(ui->updataIDeEdit->text().toInt());
             if(query.exec(updatasql))
             tableModel->setQuery("SELECT * FROM PASSWORD");
             else {
                 QMessageBox::information(this,tr("提示"),
                                            tr("update error: meybe no this id"));
             }
            if(person == "manager")
            {

             QString updatemamager =
                     QString("update MANAGER "
                             "set NAME = '%1',SEX= '%2',PERSONNEL = '%3',POST='--'"
                             "where ID = %4 ")
                            .arg(ui->updataNameEdit->text())
                            .arg(ui->updataSexComboBox->currentText())
                            .arg(person)
                            .arg(ui->updataIDeEdit->text().toInt());
                     if(query.exec(updatemamager))
                     tableModel->setQuery("SELECT * FROM MANAGER");
                     else {
                         QMessageBox::information(this,tr("提示"),
                                        tr("update error: meybe no this id"));
                     }

                    break;
            }
            else if (person == "student")
            {

             QString updatemamager =
                      QString("update STUDENT "
                               "set NAME = '%1',SEX= '%2',PERSONNEL = '%3'  "
                               "where ID = %4 ")
                            .arg(ui->updataNameEdit->text())
                            .arg(ui->updataSexComboBox->currentText())
                            .arg(person)
                            .arg(ui->updataIDeEdit->text().toInt());
                     if(query.exec(updatemamager))
                          tableModel->setQuery("SELECT * FROM STUDENT");
                     else {
                         QMessageBox::information(this,tr("提示"),
                                                  tr("update error: meybe no this id"));
                     }

                    break;
            }
            else if (person == "member")
            {
                QString updatemamager =
                      QString("update MEMBER "
                                "set NAME = '%1',SEX= '%2',PERSONNEL = '%3'  "
                                "where ID = %4")
                        .arg(ui->updataNameEdit->text())
                        .arg(ui->updataSexComboBox->currentText())
                        .arg(person)
                        .arg(ui->updataIDeEdit->text().toInt());
                 if(query.exec(updatemamager))
                      tableModel->setQuery("SELECT * FROM MEMBER");
                 else {
                     QMessageBox::information(this,tr("提示"),
                                               tr("update error: meybe no this id"));
                 }
                   break;
            }
            else {
                QMessageBox::information(this,tr("提示"),
                                           tr("出错了："));
                break;
            }


        }
    }


}

