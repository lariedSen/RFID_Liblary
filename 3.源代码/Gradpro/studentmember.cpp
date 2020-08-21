#include "studentmember.h"
#include "ui_studentmember.h"
#include"login.h"
#include<QMessageBox>
StudentMember::StudentMember(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentMember)
{
    ui->setupUi(this);
    tableModel = new myModel(this);
    ui->tableView->setModel(tableModel);
    // 打开数据库文件
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lisen.db");
    db.open();
    tableModel->setQuery("SELECT ID, NAME, PERSONNEL FROM PASSWORD");

    //正则表达式限制输入
    QRegExp reg("^[a-zA-Z0-9]+$");
    QValidator*validator = new QRegExpValidator(reg);

    QRegExp regid("^[0-9]+$");
    QValidator*validatorid = new QRegExpValidator(reg);

    //更新
    ui->updataIDeEdit->setValidator(validatorid);
    ui->updataNameEdit->setValidator(validator);
    ui->updataPasseEdit->setValidator(validator);
}

StudentMember::~StudentMember()
{
    delete ui;
}

void StudentMember::on_updateBtn_clicked()
{
//    tableModel->setQuery("SELECT * FROM PASSWORD");


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
             tableModel->setQuery(QString("SELECT * FROM  PASSWORD WHERE ID = %1").
                                  arg(id));
             else {
                 QMessageBox::information(this,tr("提示"),
                                            tr("update error: meybe no this id"));
             }

            if (person == "student")
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
                      tableModel->setQuery(QString("SELECT * FROM  STUDENT WHERE ID = %1").
                         arg(id));
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
                     tableModel->setQuery(QString("SELECT * FROM  MEMBER WHERE ID = %1").
                                                                     arg(id));
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

//返回上一级
void StudentMember::on_returnBtn_clicked()
{
        Login* l = new Login();
        l->show();
        this->close();
}

//点击确定
void StudentMember::on_eneterBtn_clicked()
{

}

void StudentMember::on_checkBtn_clicked()
{
    int id  = ui->updataIDeEdit->text().toInt();
   QString pass =  ui->updataPasseEdit->text();
   QSqlQuery query(db);
   query.exec("select * from PASSWORD");
   while(query.next())
   {
       if( (id == query.value("ID").toInt()) && (pass == query.value("PASS").toString()) )
       {
           qDebug()<<"you are right! ";
           QMessageBox::information(this,tr("提示"),
                                      tr("确认：欢迎你"));
           if(query.value("PERSONNEL").toString() == "student")
            {
            tableModel->setQuery(QString("SELECT * FROM  STUDENT WHERE ID = %1").
                                 arg(id));
           }
           else {
              tableModel->setQuery(QString("SELECT * FROM  MEMBER WHERE ID = %1").
                                   arg(id));
           }
       }
       else {
           //    Login* l = new Login();
           //    l->show();
           //this->close();

       }
   }
   ui->updataPasseEdit->clear();
   ui->updataNameEdit->clear();



}
