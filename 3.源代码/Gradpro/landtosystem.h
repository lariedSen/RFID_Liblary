#ifndef LANDTOSYSTEM_H
#define LANDTOSYSTEM_H

#include <QWidget>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QRegExpValidator>
namespace Ui {
class LandToSystem;
}


class LandToSystem : public QWidget
{
    Q_OBJECT

public:
    explicit LandToSystem(QWidget *parent = nullptr);
    ~LandToSystem();

private slots:
    void on_passBtn_clicked();

    void on_exitBtn_clicked();
    void updateProgressVaule();


private:
    Ui::LandToSystem *ui;
     QTimer* mTimer ;

     bool tiao = false ;

};

#endif // LANDTOSYSTEM_H
