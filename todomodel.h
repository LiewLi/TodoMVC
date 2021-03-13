#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QList>
#include <QAbstractListModel>
#include <QVariant>

struct TodoItem
{
    Q_GADGET
 public:
    QString title;
    enum Status {
        normal = 0,
        wip = 1,
        completed = 2,
    } ;

    Status status;
    Q_ENUM(Status)
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(Status status MEMBER status)
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


    Qt::ItemFlags flags(const QModelIndex &index) const override;
 public slots:

    void appendTodo(const TodoItem &obj);
    void deleteTodo(const QModelIndex &index);
    void toggleTodo(const QModelIndex &index);
    void updateTodoTitle(const QModelIndex &index, const QString &);

signals:

};

#endif // MODEL_H
