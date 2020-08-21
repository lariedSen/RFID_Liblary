#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<managerlogin.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db =  QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lisen.db");

    if(!db.open())
    {

        qDebug() << "open failed database" << db.lastError();
    }
    QSqlQuery query;
   QString IDsql = QString("CREATE TABLE IDCARD"
                              "( ID INT PRIMARY    KEY     NOT NULL,"
                              " IdCard         CHAR(50),"
                              "NAME              TEXT    NOT NULL,"
                              "SEX               TEXT    NOT NULL,"
                              "PERSONNEL         CHAR(50)"
                           ");");

   //判断数据库是否有某个表，
    if(!db.tables().contains("IDCARD"))
    {
        if(!query.exec(IDsql))
        {
            qDebug() << "create failed table" << db.lastError();
        }
        else {
            bool ok = query.exec("insert into IDCARD(ID,IdCard,NAME,SEX,PERSONNEL) values(101,'6fb7ff2f','李大','男','manager')");
           bool ok1 = query.exec("insert into IDCARD(ID,IdCard,NAME,SEX,PERSONNEL) values(16010,'6f750825','刘铁头','女','student')");
           bool ok2 = query.exec("insert into IDCARD(ID,IdCard,NAME,SEX,PERSONNEL) values(17010,'41c12b40','李尘','男','member')");
           bool ok3 = query.exec("insert into IDCARD(ID,IdCard,NAME,SEX,PERSONNEL) values(00000,'888653','游客','X','X')");

        qDebug()<<ok<<ok1<<ok2<<ok3;
        }
    }

    QString Managersql = QString("	CREATE TABLE MANAGER("
                                 "ID INT PRIMARY    KEY     NOT NULL,"
                                 "NAME              TEXT    NOT NULL,"
                                 " SEX               TEXT    NOT NULL,"
                                 "PERSONNEL         CHAR(50),"
                                 " POST              TEXT    NOT NULL"
                                 " );");

    //判断数据库是否有MANAGER表，
     if(!db.tables().contains("MANAGER"))
     {
         if(!query.exec(Managersql))
         {
             qDebug() << "create failed table" << db.lastError();
         }
         else
         {

            bool ok = query.exec("insert into MANAGER(ID,NAME,SEX,PERSONNEL,POST) values(101,'李大','男','manager','图书馆长')");
            bool ok1 = query.exec("insert into MANAGER(ID,NAME,SEX,PERSONNEL,POST) values(103,'陈真','男','manager','行政人员')");
            bool ok2 = query.exec("insert into MANAGER(ID,NAME,SEX,PERSONNEL,POST) values(104,'曹四','女','manager','安全部长')");
         qDebug()<<ok<<ok1<<ok2;
         }
     }

     QString STUDENTsql = QString("	CREATE TABLE STUDENT("
                                  "ID INT PRIMARY    KEY     NOT NULL,"
                                  " NAME              TEXT    NOT NULL,"
                                  "SEX               TEXT    NOT NULL,"
                                  "PERSONNEL         CHAR(50)"
                                  " );");

     //判断数据库是否有STUDENT表，
      if(!db.tables().contains("STUDENT"))
      {
          if(!query.exec(STUDENTsql))
          {
              qDebug() << "create failed table" << db.lastError();
          }
          else
          {

             bool ok = query.exec("insert into STUDENT(ID,NAME,SEX,PERSONNEL) values(16010,'李二狗','男','student')");
             bool ok1 = query.exec("insert into STUDENT(ID,NAME,SEX,PERSONNEL) values(16011,'刘铁头','女','student')");
             bool ok2 = query.exec("insert into STUDENT(ID,NAME,SEX,PERSONNEL) values(16012,'诸葛山珍','女','student')");
          qDebug()<<ok<<ok1<<ok2;
          }
      }
      QString Membersql = QString("	CREATE TABLE MEMBER("
                                  "ID INT PRIMARY    KEY     NOT NULL,"
                                  "NAME              TEXT    NOT NULL,"
                                  "SEX               TEXT    NOT NULL,"
                                  " PERSONNEL         CHAR(50)"
                                  ");");

      //判断数据库是否有MEMBER表，
       if(!db.tables().contains("MEMBER"))
       {
           if(!query.exec(Membersql))
           {
               qDebug() << "create failed table" << db.lastError();
           }
           else
           {

              bool ok = query.exec("insert into MEMBER(ID,NAME,SEX,PERSONNEL) values(17010,'李尘','男','member')");
              bool ok1 = query.exec(" insert into MEMBER(ID,NAME,SEX,PERSONNEL) values(17011,'刘晨','男','member')");
              bool ok2 = query.exec("insert into MEMBER(ID,NAME,SEX,PERSONNEL) values(00000,'游客',' ','  ')");
           qDebug()<<ok<<ok1<<ok2;
           }
       }
       QString Landingsql = QString("	CREATE TABLE LANDING("
                                    "ID INT PRIMARY    KEY     NOT NULL,"
                                    "NAME              TEXT    NOT NULL,"
                                    "SEX               TEXT    NOT NULL,"
                                    "PERSONNEL         CHAR(50),"
                                    " TIME              CHAR(50)"
                                    ");");

       //判断数据库是否有LANDING表，
        if(!db.tables().contains("LANDING"))
        {
            if(!query.exec(Landingsql))
            {
                qDebug() << "create failed table" << db.lastError();
            }
            else
            {

               bool ok = query.exec("insert into LANDING(ID,NAME,SEX,PERSONNEL,TIME) values(1,'--','--' ,'-','-')");

            qDebug()<<ok;
            }
        }
        QString passsql = QString("CREATE TABLE PASSWORD("
                                  "ID INT PRIMARY    KEY     NOT NULL,"
                                  " PASS              CHAR(10) ,"
                                  "NAME              TEXT    NOT NULL,"
                                  "PERSONNEL         CHAR(50)"
                                  ");");

        //判断数据库是否有PASSWORD表，
         if(!db.tables().contains("PASSWORD"))
         {
             if(!query.exec(passsql))
             {
                 qDebug() << "create failed table" << db.lastError();
             }
             else
             {
                 bool ok = query.exec("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) values(101,'101','李大','manager')");
                 bool ok1 = query.exec("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) values(103,'103','陈真','manager')");
                 bool ok2 = query.exec("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) values(104,'104','曹四','manager')");

                 bool ok3 = query.exec("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) values(16010,'16010','李二狗','student')");
                 bool ok4 = query.exec("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) values(16011,'16011','刘铁头','student')");
                 bool ok5 = query.exec("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) values(16012,'16012','诸葛生珍','student')");
                 bool ok6 = query.exec("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) values(17010,'17010','李尘','member')");
                 bool ok7 = query.exec("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) values(17011,'17011','刘晨','member')");
                 bool ok8 = query.exec("insert into PASSWORD(ID,PASS,NAME,PERSONNEL) values(00000,'00000','游客','  ')");
             qDebug()<<ok<<ok1<<ok2<<ok3<<ok4<<ok5<<ok6<<ok7<<ok8;
             }
         }
         QString Liusql = QString("	CREATE TABLE PEOPLEMOVE("
                                  "ID INT PRIMARY    KEY     NOT NULL,"
                                  "NAME              TEXT    NOT NULL,"
                                  "SEX               TEXT    NOT NULL,"
                                  "PERSONNEL         CHAR(50),"
                                  "TIME              CHAR(50)"
                                  ");");

         //判断数据库是否有PASSWORD表，
          if(!db.tables().contains("PEOPLEMOVE"))
          {
              if(!query.exec(Liusql))
              {
                  qDebug() << "create failed table" << db.lastError();
              }
              else
              {

              }
          }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_onbtn_clicked()
{

    qDebug()<<"你好，图书馆欢迎你";
    this->l.show();
    this->hide();
//    ManagerLogin * m = new ManagerLogin();
//    m->show();


}

void MainWindow::on_offBtn_clicked()
{
    qDebug()<<"期待你下次的光临";
    this->close();
    QApplication * app;
    app->exit(0);
}
