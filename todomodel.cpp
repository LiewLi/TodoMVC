#include "todomodel.h"

TodoModel::TodoModel(QObject *parent): QAbstractListModel(parent)
{
    todos = new QList<TodoItem>();
}

int TodoModel::rowCount(const QModelIndex &parent) const
{
    return todos->count();
}


QVariant TodoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

       QVariant var;
       var.setValue(todos->at(index.row()));
       return var;
}

bool TodoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole) return false;
    TodoItem &obj = (*todos)[index.row()];
    obj = value.value<TodoItem>();
    emit dataChanged(index, index);
    return true;
}


void TodoModel::appendTodo(const TodoItem &obj)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    todos->append(obj);
    endInsertRows();
}

void TodoModel::deleteTodo(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    todos->remove(index.row(), 1);
    endRemoveRows();
}


void TodoModel::toggleTodo(const QModelIndex &index)
{
    TodoItem &obj =  (*todos)[index.row()];
    obj.status = obj.status == TodoItem::normal ? TodoItem::completed :  TodoItem::normal;
    QVariant var;
    var.setValue(obj);
    setData(index, var);
}

void TodoModel::updateTodoTitle(const QModelIndex &index, const QString & str)
{
    TodoItem &obj =  (*todos)[index.row()];
    obj.title = str;
    QVariant var;
    var.setValue(obj);
    setData(index, var);

}

Qt::ItemFlags TodoModel::flags(const QModelIndex &index) const
{
    return Qt::ItemFlag::ItemIsEditable | Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable;
}
