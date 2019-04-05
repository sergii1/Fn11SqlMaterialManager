#include "mytablewidget.h"
#include "ui_mytablewidget.h"

MyTableWidget::MyTableWidget(QSqlQueryModel* p_model,const QString& p_tableName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTableWidget)
{
    ui->setupUi(this);
    ui->label->setText(p_tableName);
    ui->tableView->setModel(p_model);

}

QTableView* MyTableWidget::getView(){
    return ui->tableView;
}
QAbstractItemModel* MyTableWidget::getModel(){
    return ui->tableView->model();
}

QLabel* MyTableWidget::getLabel(){
    return  ui->label;
}
void MyTableWidget::setModel(QSqlQueryModel* p_model){
    ui->tableView->setModel(p_model);
}

void MyTableWidget::setText(const QString& p_text){
    ui->label->setText(p_text);
}

QPushButton* MyTableWidget::getButton(){
    return ui->pushButton;
}

MyTableWidget::~MyTableWidget()
{
    delete ui;
}
