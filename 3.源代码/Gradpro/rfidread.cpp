#include "rfidread.h"
#include "ui_rfidread.h"
#include <QMessageBox>
#include <QDebug>
#include"systemopen.h"
#include<QDateTime>
RFidRead::RFidRead(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RFidRead)
{
    ui->setupUi(this);
    this->resize(800,480);
    // 信号与槽
    connect(&timer, SIGNAL(timeout()), this, SLOT(detectCard()));
    connect(this, SIGNAL(onDeteced()), this, SLOT(getCardNumber()));

    datatime = new QDateTime(QDateTime::currentDateTime());


    db =  QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lisen.db");
    if(!db.open())
    {

        qDebug() << "open failed database" << db.lastError();
    }

}


RFidRead::~RFidRead()
{
    delete ui;
}



void RFidRead::on_pushButtonSerial_clicked(bool checked)
{
    // 按下了开始刷卡的按钮
    if(checked)
    {
        // 更新控件的状态
        ui->pushButtonSerial->setText("停止刷卡");
        ui->comboBoxTTY->setEnabled(false);
        ui->comboBoxBaud->setEnabled(false);

        // 打开相应的串口文件，并初始化之
        initTTY();

        // 开启定时器，不断探测卡片是否在能量范围之内
        timer.start(200);
    }
    else
    {

    }
}

void RFidRead::detectCard()
{
    // 初始化好卡片探测指令
    init_REQUEST();

    // 向串口发送指令
    write(ttyfd, PiccRequest_ALL, PiccRequest_ALL[0]);

    usleep(20*1000);

    // 读取串口的响应
    char recvinfo[128];
    bzero(recvinfo, 128);
    read(ttyfd, recvinfo, 128);

    // 判断应答帧的状态
    if(recvinfo[2] == 0)
    {
        qDebug() << tr("detected your card!");
        emit onDeteced();
    }
}

void RFidRead::getCardNumber()
{
        // 1.初始化好卡片防碰撞指令
       init_ANTICOLL();

       // 2.向串口发送指令
       write(ttyfd, PiccAnticoll1, PiccAnticoll1[0]);
       usleep(20*1000);

       // 3.读取串口的响应
       char recvinfo[128];
       bzero(recvinfo, 128);
       read(ttyfd, recvinfo, 128);

       // 4.读取卡号
       if(recvinfo[2] == 0)
       {
          //qDebug() << tr("card ok !!!");
          for( i=recvinfo[3]-1,j=0;i>=0;i--,j++)
          {
               memcpy((char *)&cardID+j,&recvinfo[4+i],1);
          }

          // 4.1 判断是否为同一张卡
          Cardid = ui->IDcard->text().toInt(&ok,16);
           if(cardID ==  Cardid) //判断是否同一张卡
           {
               printf("cardid = %#x\n",Cardid);
               qDebug()<<tr("please next card . this is a save caed!")<<endl;
               usleep(10*1000);
               beep(1);
               //exit(0);
           }
           else {
               //打印ID卡号并显示到屏上
               printf("cardid = %#x\n",cardID);
               QString Idcard = QString::number(cardID,16);
               qDebug()<<"cardid =  "<<Idcard<<endl;

//               ui->IDcard->setText(Idcard);
//               ui->nameLabel->setText("李大");
//               ui->sexLabel->setText("男");
//               ui->memberLabel->setText("manager");
                //timeLabel

                QSqlQuery query(db);
                query.exec("select * from IDCARD");
                while(query.next())
                {
                    if(Idcard == query.value("IdCard").toString())
                    {
                        ui->IDcard->setText(Idcard);
                        ui->nameLabel->setText(query.value("NAME").toString());
                        ui->sexLabel->setText(query.value("SEX").toString());
                        ui->memberLabel->setText(query.value("PERSONNEL").toString());
                        ui->timeLael->setText(QString("%1").arg(datatime->time().toString()));
                        QString info =
                                QString("insert into PEOPLEMOVE(ID,NAME,SEX,PERSONNEL,TIME)  "
                                         "values(%1,'%2','%3' ,'%4','%5');")
                                           .arg(query.value("ID").toInt())
                                           .arg(query.value("NAME").toString())
                                           .arg(query.value("SEX").toString())
                                           .arg(query.value("PERSONNEL").toString())
                                           .arg(datatime->time().toString());
                                            bool isok =  query.exec(info);
                                            qDebug() << isok;
                    }
                }

                beep(0);
           }
           sleep(2);

       }
//       else{
//                 printf("get cardid error!\n");
//                 exit(-1);
//           }

}


void RFidRead::beep(int card_no)
{
   //0. 访问蜂鸣器
       int beep_fd = open("/dev/beep",O_RDWR);
       int i;
    if(!card_no )
    {
        ioctl(beep_fd,0,1);
        usleep(500000);
        ioctl(beep_fd,1,1);

    }
    //刷了相同的卡
    else{
         for(i=0;i<3;i++)
         {
            ioctl(beep_fd,0,1);
             usleep(100000);
             ioctl(beep_fd,1,1);
             usleep(100000);
          }
         }


}


void RFidRead::initTTY()
{
    // 根据下拉框选项初始化串口
    const char *tty = QString("/dev/%1").arg(ui->comboBoxTTY->currentText()).toStdString().c_str();
    ttyfd = open(tty, O_RDWR);
    if(ttyfd == -1)
    {
        QMessageBox::critical(this, "错误", strerror(errno));
        exit(0);
    }

    // 声明串口的配置结构体
    struct termios config;
    bzero(&config, sizeof(config));

    // 设置无奇偶校验
    // 设置数据位为8位
    // 设置非规范模式（原生模式）
    cfmakeraw(&config);

    // 波特率
    switch(ui->comboBoxBaud->currentText().toInt())
    {
    case 9600:cfsetspeed(&config, B9600); break;
    case 115200:cfsetspeed(&config, B115200); break;
    }

    // 1位停止位、1位起始位
    config.c_cflag &= ~CSTOPB;
    config.c_cflag |= (CREAD|CLOCAL);

    config.c_cc[VTIME] = 0;
    config.c_cc[VMIN]  = 1;

    tcsetattr(ttyfd, TCSANOW, &config);
}

void RFidRead::on_return_2_clicked()
{
    this->close();
    SystemOpen * s = new SystemOpen();
    s->show();


}
