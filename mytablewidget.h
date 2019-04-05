#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QWidget>

namespace Ui {
class MyTableWidget;
}

class MyTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyTableWidget(QWidget *parent = nullptr);
    ~MyTableWidget();

private:
    Ui::MyTableWidget *ui;
};

#endif // MYTABLEWIDGET_H
