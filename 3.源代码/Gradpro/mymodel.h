#ifndef MYMODEL_H
#define MYMODEL_H

#include <QSqlQueryModel>
#include <QWidget>

class myModel : public QSqlQueryModel
{
public:
    myModel(QWidget *parent);

    // 复写相关虚函数
    // 1, 规定数据表格中每一项的权限标签
    Qt::ItemFlags flags(const QModelIndex &index) const;

    // 2，读取数据库数据
    // item: 一条记录中的某一个字段
    // role: 字段内容中的某一个角色（比如文本、颜色、对齐方式……）
    QVariant data(const QModelIndex &item, int role) const;

    // 3，设置数据库数据
    // item : 一条记录中的某一个字段
    // role : 字段内容中的某一个角色（比如文本、颜色、对齐方式……）
    // value: 角色的具体的值（比如文本的内容、颜色的色号、居左或者居右……）
    bool setData(const QModelIndex &index, const QVariant &value, int role);
};

#endif // MYMODEL_H
