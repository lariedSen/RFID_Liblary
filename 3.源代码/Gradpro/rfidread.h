#ifndef RFIDREAD_H
#define RFIDREAD_H

#include <QWidget>
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>
#include<QDateTime>
#include "iso14443a.h"

namespace Ui {
class RFidRead;
}

class RFidRead : public QWidget
{
    Q_OBJECT

public:
    explicit RFidRead(QWidget *parent = nullptr);
    ~RFidRead();

private slots:

    void detectCard();    // 探测卡片
    void getCardNumber(); // 读取卡号

// 当我发现有卡片在附近的时候，发出信号
    void on_pushButtonSerial_clicked(bool checked);

    void on_return_2_clicked();

signals:
    void onDeteced();

private:
    Ui::RFidRead *ui;
    void initTTY(); // 初始化（配置）串口: 波特率、数据位、停止位……
    void closeTTY();

    void beep(int card_no);
    int ttyfd; // 串口文件描述符
    int cardID , i, j;
     int Cardid = 0;
      bool ok ;
    QTimer timer;
     QDateTime * datatime ;
    QSqlDatabase db;
    int CardId;
};



#endif // RFIDREAD_H
