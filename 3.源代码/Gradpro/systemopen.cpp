#include "systemopen.h"
#include "ui_systemopen.h"
#include "landtosystem.h"
#include<QDebug>
//#include"rfid_ka.h"

SystemOpen::SystemOpen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemOpen)
{
    ui->setupUi(this);
    this->resize(900,480);
}

SystemOpen::~SystemOpen()
{
    delete ui;
}

void SystemOpen::on_openBtn_clicked()
{

    this->r.show();
    this->close();
    qDebug()<<tr("欢迎来到打卡界面");

}

void SystemOpen::on_onBtn_clicked()
{
    qDebug()<<tr("开启登陆界面");
    this->l.show();
    this->hide();
}

void SystemOpen::on_returnBtn_clicked()
{
    LandToSystem * l = new LandToSystem();
    l->show();
    this->close();
}
