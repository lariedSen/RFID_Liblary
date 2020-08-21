#include "login.h"
#include "ui_login.h"
#include"systemopen.h"
#include<QDateTime>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

//    connect(this,SIGNAL( ManagerSigned() ),this,SLOT( Manager()) );
//    connect(this,SIGNAL(StudentSigned() ),this,SLOT(Student()) );
//    connect(this,SIGNAL(OtherSigned() ),this,SLOT(Other()) );

    this->resize(800,480);
    //打开数据库
    db =  QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lisen.db");
    if(!db.open())
    {

        qDebug() << "open failed database" << db.lastError();
    }

    //正则表达式限制输入
    QRegExp reg1("^[0-9]+$");
    QValidator*validator1 = new QRegExpValidator(reg1);
    ui->idLineEdit->setValidator(validator1);

    QRegExp reg("^[a-zA-Z0-9]+$");
    QValidator*validator = new QRegExpValidator(reg);
    ui->passLineEdit->setValidator(validator);

}
Login::~Login()
{
    delete ui;
}

void Login::on_returnBtn_clicked()
{
        SystemOpen * l =new SystemOpen();
        l->show();
        this->close();
}

/***
    进入管理员界面
**/
void Login::Manager(int id )
{
      QSqlQuery query(db);
      QDateTime * datatime = new QDateTime(QDateTime::currentDateTime());

      //1. 先查询 MANAGER 表格,得到信息
      query.exec("select * from MANAGER");//ID,NAME,SEX,PERSONNEL,POST
      while(query.next())
      {
          //先读出来
          int Id_1 = query.value("ID").toInt();
          QString sex = query.value("SEX").toString();
          QString name = query.value("NAME").toString();
          QString personel = query.value("PERSONNEL").toString();

          qDebug() <<"id ="<< id << " sex =  "<<sex <<" name ="<<name
          << "personel = " << personel ;

          //2. 信息写入到表格LANDING
          if(id == Id_1)
          {
            QString info = QString("insert into LANDING (ID,NAME,SEX,PERSONNEL,TIME) "
                                   "values(%1,'%2','%3','%4','%5')")
                    .arg(id)
                    .arg(name)
                    .arg(sex)
                    .arg(personel)
                    .arg(datatime->time().toString());
            bool isok =  query.exec(info);
            qDebug() << isok;


          }
    }

    qDebug()<<"管理员界面";
        this->m.show();
        this->close();


}

/***
 * 登陆用户界面
*/
void Login::Student(int id )
{

    QSqlQuery query;
    QDateTime * datatime = new QDateTime(QDateTime::currentDateTime());
    //1. 先查询 MANAGER 表格,得到信息
    query.exec("select * from STUDENT");//ID,NAME,SEX,PERSONNEL
    while(query.next())
    {
        //先读出来
        int Id_1 = query.value("ID").toInt();
        QString name = query.value("NAME").toString();
        QString sex = query.value("SEX").toString();
        QString personel = query.value("PERSONNEL").toString();

        qDebug() <<"id ="<< id << " sex =  "<<sex <<" name ="<<name
        << "personel = " << personel ;

        //2. 信息写入到表格LANDING
        if(id == Id_1)
        {
          QString info = QString("insert into LANDING (ID,NAME,SEX,PERSONNEL,TIME) "
                                 "values(%1,'%2','%3','%4','%5')")
                  .arg(id)
                  .arg(name)
                  .arg(sex)
                  .arg(personel)
                  .arg(datatime->time().toString());
          bool isok =  query.exec(info);
          qDebug() << isok;
        }
  }

    qDebug()<<"学生或者会员界面";
        this->s.show();
        this->close();
//    db.close();
}

/***
 * 登陆游客界面
*/
void Login::Other( int id )
{
    qDebug()<<"游客界面";
        this->o.show();
       this->close();
//     db.close();
}

void Login::on_enterBtn_clicked()
{
    QSqlQuery query;
    query.exec("select * from PASSWORD");

    while(query.next())
    {
        //先读出来
        int id = query.value("ID").toInt();
        QString pass = query.value("PASS").toString();
        QString name = query.value("NAME").toString();
        QString personel = query.value("PERSONNEL").toString();
        qDebug() <<"id ="<< id << " pass =  "<<pass <<" name ="<<name ;

        //对比
        QString passDui = ui->passLineEdit->text() ;
        if(  (id == ui->idLineEdit->text().toInt())
             && (pass == passDui) )
        {
            if(personel == "manager")
            {
                Manager(id );
            }
            else if ( ( personel == "student" ) || ( personel == "member") )
            {
                Student(id);
            }
            else
            {
                Other(id);
            }

        }
    }


}
