#ifndef TODOMODEL_H
#define TODOMODEL_H

#include <QObject>
#include <QList>
#include <QAbstractListModel>
#include <QVariant>

struct TodoItem
{
 public:
    QString title;
    enum Status {
        normal = 0,
        wip = 1,
        completed = 2,
    } ;

    Status status;
};
Q_DECLARE_METATYPE(TodoItem);

class TodoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TodoModel(QObject *parent = nullptr);
    QList<TodoItem> *todos;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void appendTodo(const TodoItem &obj);
    void deleteTodo(const QModelIndex &index);
    void toggleTodo(const QModelIndex &index);

    Qt::ItemFlags flags(const QModelIndex &index) const override;

signals:

};

#endif // TODOMODEL_H
