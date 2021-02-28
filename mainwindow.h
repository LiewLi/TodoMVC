#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>

#include "todomodel.h"
#include "todoitemdelegate.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QListView *m_view;
    QPushButton *m_addBtn;
    QPushButton *m_delBtn;
    QPushButton *m_toggleBtn;

    TodoModel *m_model;
    TodoItemDelegate *m_delegate;


    void appendItem();
    void removeItem();
    void toggleCompleted();
};
#endif // MAINWINDOW_H
