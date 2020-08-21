#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "keyBoard.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    keyBoard k;
    k.hide();

    MainWindow w;
    w.show();

    return a.exec();
}
