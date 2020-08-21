#include "landtosystem.h"
#include "ui_landtosystem.h"
#include "systemopen.h"
#if 0

#endif
#include <QMessageBox>
#include <QTimer>
#include "QDebug"
#include "mainwindow.h"
#include <QDateTime>
#include<QTextStream>
LandToSystem::LandToSystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LandToSystem)
{
    ui->setupUi(this);
    //设置时间
    QDateTime * datatime = new QDateTime(QDateTime::currentDateTime());
//    QString time = QString("data : %1 , time: %2").arg(datatime->date().toString()).
//            arg(datatime->time().toString());

    ui->dataLabel->setText(QString("%1").arg(datatime->date().toString() ) );
    ui->timeLabel->setText(QString("%1").arg(datatime->time().toString()));

    QRegExp reg("^[a-zA-Z0-9]+$");
    QValidator*validator = new QRegExpValidator(reg);
    ui->passEdit->setValidator(validator);
}

LandToSystem::~LandToSystem()
{
    delete ui;
}

void LandToSystem::on_passBtn_clicked()
{
   QString SudoPassword =  ui->passEdit->text();
    qDebug()<<"请输入密码";

    //定时器
    mTimer = new QTimer(this);
        connect(mTimer,SIGNAL(timeout()),
                this,SLOT(updateProgressVaule()));

   if(SudoPassword == "lisen")
   {
       qDebug()<<"进入下一级界面";

       ui->passinLabel->setText(tr("密码正确"));
         QMessageBox::information(this,tr("图书馆欢迎您，"),
                                  tr(",1s后马上进入.请确认"));
         mTimer->start(1000); //单位为毫秒
         SudoPassword = QString("00");
   }
   else {
       ui->passinLabel->setText(tr("密码错误，请输入"));
   }
    ui->passEdit->clear();
}

//定时器的槽函数
void LandToSystem::updateProgressVaule()
{
        mTimer->stop();
        SystemOpen * s = new SystemOpen();
        s->show();
        this->close();
}


void LandToSystem::on_exitBtn_clicked()
{  
    MainWindow * s  = new MainWindow();
    s->show();
    this->close();
}
