#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QtWidgets>
#include <QtSql/QSqlQueryModel>

namespace Ui {
class MyTableWidget;
}

class MyTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyTableWidget(QSqlQueryModel* p_model,const QString& p_tableName,QWidget *parent = nullptr);
    ~MyTableWidget();
    QTableView* getView();
    QAbstractItemModel* getModel();
    QLabel* getLabel();
    void setModel(QSqlQueryModel* p_model);
    void setText(const QString& p_text);
    QPushButton* getButton();

private:
    Ui::MyTableWidget *ui;
};

#endif // MYTABLEWIDGET_H
