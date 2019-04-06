#include "mytreewidget.h"
#include "ui_mytreewidget.h"

MyTreeWidget::MyTreeWidget(const QString& p_tableName, TreeModel* p_model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTreeWidget)
{
    ui->setupUi(this);
    ui->label->setText(p_tableName);
    ui->treeView->setModel(p_model);
}

QTreeView* MyTreeWidget::getView(){
    return ui->treeView;
}

QAbstractItemModel* MyTreeWidget::getModel(){
    return ui->treeView->model();
}

QLabel* MyTreeWidget::getLabel(){
    return  ui->label;
}
void MyTreeWidget::setModel(QSqlQueryModel* p_model){
    ui->treeView->setModel(p_model);
}

void MyTreeWidget::setText(const QString& p_text){
    ui->label->setText(p_text);
}

QPushButton* MyTreeWidget::getButton(){
    return ui->pushButton;
}

void MyTreeWidget::setStyleSheet(const QString& p_qss){
    ui->label->setStyleSheet(p_qss);
    ui->pushButton->setStyleSheet(p_qss);
}

MyTreeWidget::~MyTreeWidget()
{
    delete ui;
}
