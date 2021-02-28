#include "mainwindow.h"
#include <QtWidgets/QToolBar>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QInputDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("ToDoX"));
    setMinimumHeight(600);
    setMinimumWidth(400);

    m_view = new QListView(this);

    QFrame *frame = new QFrame(this);
    QVBoxLayout *layout = new QVBoxLayout(frame);
    layout->addWidget(m_view);

    QToolBar *toolBar = new QToolBar(frame);
    toolBar->setFixedHeight(40);

    m_addBtn = new QPushButton();
    m_addBtn->setText("Add");
    m_addBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(m_addBtn);

    QObject::connect(m_addBtn, &QPushButton::clicked, this, &MainWindow::appendItem);

    m_delBtn = new QPushButton();
    m_delBtn->setText("Delete");
    m_delBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(m_delBtn);

    QObject::connect(m_delBtn, &QPushButton::clicked, this, &MainWindow::removeItem);

    m_toggleBtn = new QPushButton();
    m_toggleBtn->setText("Toggle");
    m_toggleBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(m_toggleBtn);

    QObject::connect(m_toggleBtn, &QPushButton::clicked, this, &MainWindow::toggleCompleted);

    layout->addWidget(toolBar);

    setCentralWidget(frame);

    m_model = new TodoModel();
    m_delegate = new TodoItemDelegate(this);
    m_view->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    m_view->setModel(m_model);
    m_view->setItemDelegate(m_delegate);
}

MainWindow::~MainWindow()
{
}

void MainWindow::appendItem()
{
    qDebug() << "append item";

    bool ok;
    QString txt = QInputDialog::getText(this, "Add Todo", "New Todo:", QLineEdit::Normal, "", &ok);

    if (ok && !txt.isEmpty()) {
        TodoItem obj;
        obj.title = txt;
        obj.status = TodoItem::normal;
        m_model->appendTodo(obj);
    }
}

void MainWindow::removeItem()
{
    qDebug() << "remove item";

    const QItemSelectionModel *selection =  m_view->selectionModel();
    if (selection == nullptr) return;
    const QModelIndexList &indexList = selection->selectedIndexes();
    if (indexList.isEmpty()) return;
    m_model->deleteTodo(indexList[0]);
}

void MainWindow::toggleCompleted()
{
    qDebug() << "toggle completed";
    const QItemSelectionModel *selection =  m_view->selectionModel();
    if (selection == nullptr) return;
    const QModelIndexList &indexList = selection->selectedIndexes();
    if (indexList.isEmpty()) return;
    m_model->toggleTodo(indexList[0]);
}

