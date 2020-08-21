#ifndef SYSTEMOPEN_H
#define SYSTEMOPEN_H

#include <QWidget>
#include "login.h"
#include"rfidread.h"
namespace Ui {
class SystemOpen;
}

class SystemOpen : public QWidget
{
    Q_OBJECT

public:
    explicit SystemOpen(QWidget *parent = nullptr);
    ~SystemOpen();

private slots:
    void on_openBtn_clicked();

    void on_onBtn_clicked();

    void on_returnBtn_clicked();

private:
    Ui::SystemOpen *ui;
    Login l;
    RFidRead r;
};

#endif // SYSTEMOPEN_H
