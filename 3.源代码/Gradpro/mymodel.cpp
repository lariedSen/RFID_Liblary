#include "mymodel.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

myModel::myModel(QWidget *parent)
    :QSqlQueryModel(parent)
{

}

Qt::ItemFlags myModel::flags(const QModelIndex &index) const
{
    // 获取系统默认的每一数据项的权限标签f
    // index: 索引，即某行某列
    Qt::ItemFlags f;
    f = QSqlQueryModel::flags(index);

    // 如果是第三列的数据
    if(index.column() == 3)
    {
        // 那么加上可编辑权限
        return f|=Qt::ItemIsEditable;
    }

    // 返回修改之后的权限标签f
    return f;
}

// 读取数据库数据
// item: 一条记录中的某一个字段
// role: 字段内容中的某一个角色（比如文本、颜色、对齐方式……）
QVariant myModel::data(const QModelIndex &item, int role) const
{
    // 根据系统的默认规则，取得某行某列的某种角色的值
    QVariant value = QSqlQueryModel::data(item, role);

    // 如果当前获取的是第三列（产地）的数据
    // 并且当前是这个数据的颜色的值
    if(item.column() == 3 && role==Qt::TextColorRole)
    {
        // 那么统统返回蓝色
        return QColor(Qt::blue);
    }

    // 返回修改之后的值
    return value;
}

// item : 一条记录中的某一个字段
// role : 字段内容中的某一个角色（比如文本、颜色、对齐方式……）
// value: 角色的具体的值（比如文本的内容、颜色的色号、居左或者居右……）
bool myModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // 根据系统的默认规则，修改指定的数据模型的中某行某列的某种角色的值
    bool ok = QSqlQueryModel::setData(index, value, role);

    // 获得当前正在修改的数据项的序号
    QModelIndex IDIndex = QSqlQueryModel::index(index.row(), 0);
    int id = QSqlQueryModel::data(IDIndex).toInt();

    QSqlQuery query;

    // 修改第三列（产地）
    qDebug() << index.column();
    if(index.column() == 3)
    {
        query.prepare("UPDATE guns SET 产地=? WHERE 序号=?");
        query.bindValue(0, value.toString());
        query.bindValue(1, id);
    }

    ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastError().text();
    }

    // 重新记载数据库的数据
    this->setQuery("SELECT * FROM guns");
    return ok;
}
