#include "todoitemdelegate.h"
#include "todomodel.h"

#include <QPainter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QStyle>
#include <QColor>
#include <QFont>
#include <QString>

TodoItemDelegate::TodoItemDelegate(QObject *parent): QStyledItemDelegate(parent)
{

}


QWidget* TodoItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QTextEdit *edit = new QTextEdit(parent);
    edit->setAlignment(Qt::AlignCenter);
    return edit;
}

void TodoItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QTextEdit *edit = static_cast<QTextEdit *>(editor);
    const TodoModel *todoModel = static_cast<const TodoModel *>(index.model());
    QVariant obj = todoModel->data(index, Qt::EditRole);
    edit->setText(obj.value<TodoItem>().title);
}

void TodoItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QTextEdit *edit = static_cast<QTextEdit *>(editor);
    const TodoModel *todoModel = static_cast<const TodoModel *>(index.model());
    QVariant var =  todoModel->data(index, Qt::EditRole);
    var.value<TodoItem>().title = edit->toPlainText();
    model->setData(index, var);
}

QSize TodoItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.size().width(), 80);
}

void TodoItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    QRect rect = option.rect;
    const TodoModel *todoModel = static_cast<const TodoModel *>(index.model());

    QVariant obj = todoModel->data(index, Qt::DisplayRole);
    const TodoItem &item = obj.value<TodoItem>();
    if (option.state.testFlag(QStyle::StateFlag::State_Selected)) {
      QBrush brush(QColorConstants::DarkCyan);
      painter->fillRect(rect, brush);
    } else {
        painter->fillRect(rect, option.backgroundBrush);
    }
    QFont f;
    f.setStyleHint(QFont::Monospace);
    f.setPixelSize(30);

    f.setStrikeOut(item.status == TodoItem::completed);
    f.setItalic(item.status == TodoItem::completed);
    painter->setFont(f);

    painter->setPen(item.status == TodoItem::completed ?  QColorConstants::Gray : QColorConstants::White);

     QString str =  QString("%1").arg(item.title);

    painter->drawText(QPoint(rect.left() + 10, rect.top() + rect.height() / 2 + 30 / 2) ,  str);
    painter->restore();
}

void TodoItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
