#include "othermember.h"
#include "ui_othermember.h"
#include"login.h"
#include<QMessageBox>
OtherMember::OtherMember(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtherMember)
{
    ui->setupUi(this);
    this->resize(800,480);

    tableModel = new myModel(this);
    ui->tableView->setModel(tableModel);
    // 打开数据库文件
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lisen.db");
    db.open();
    tableModel->setQuery("SELECT * FROM MEMBER");

    //正则表达式限制输入
    QRegExp reg("^[a-zA-Z0-9]+$");
    QValidator*validator = new QRegExpValidator(reg);

    QRegExp regid("^[0-9]+$");
    QValidator*validatorid = new QRegExpValidator(reg);

    //更新
//    ui->updataIDeEdit->setValidator(validatorid);
//    ui->updataNameEdit->setValidator(validator);
//    ui->updataPasseEdit->setValidator(validator);

    ui->IDLineEDit->setValidator(validatorid);
    ui->NameLineEdit->setValidator(validator);
     ui->passLineEDit->setValidator(validator);

}

OtherMember::~OtherMember()
{
    delete ui;
}

void OtherMember::on_returnBtn_clicked()
{
    Login* l = new Login();
    l->show();
    this->close();
}

void OtherMember::on_enterBtn_clicked()
{
    int id = ui->IDLineEDit->text().toInt();
    QString pass = ui->passLineEDit->text();
    QString name = ui->NameLineEdit->text();
     QString sex = ui->SexComboBox->currentText();

    QSqlQuery query(db);
    query.exec("select * from MEMBER");
    QString addsql =QString("insert into MEMBER(ID,NAME,SEX,PERSONNEL) "
                            "values(%1,'%2','%3','member')")
            .arg(id)
            .arg(name)
            .arg(sex);

    QString passsql =QString("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) "
                            "values(%1,'%2','%3','member')")
            .arg(id)
            .arg(pass)
            .arg(name);

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
