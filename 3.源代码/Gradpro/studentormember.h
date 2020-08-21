#ifndef STUDENTORMEMBER_H
#define STUDENTORMEMBER_H

#include <QWidget>

namespace Ui {
class StudentOrMember;
}

class StudentOrMember : public QWidget
{
    Q_OBJECT

public:
    explicit StudentOrMember(QWidget *parent = nullptr);
    ~StudentOrMember();

private:
    Ui::StudentOrMember *ui;
};

#endif // STUDENTORMEMBER_H
