#include "studentormember.h"
#include "ui_studentormember.h"

StudentOrMember::StudentOrMember(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentOrMember)
{
    ui->setupUi(this);
    this->resize(800,480);
}

StudentOrMember::~StudentOrMember()
{
    delete ui;
}
