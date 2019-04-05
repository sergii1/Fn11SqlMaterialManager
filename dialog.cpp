#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

bool Dialog::needInsert = false;
QString Dialog::description = "";
QString Dialog::name = "";

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    Dialog::name = "";
    Dialog::description = "";
    Dialog::needInsert = false;
    ui->setupUi(this);
}

QString Dialog::getName(){
    return Dialog::name;
}

QString Dialog::getDescription(){
    return Dialog::description;
}

Dialog::~Dialog()
{
    delete ui;
    qDebug()<<"dialog destuctor";
    QString str1 = Dialog::name;
    QString str2 = Dialog::description;
    qDebug()<<str1<<str2;
}


void Dialog::on_buttonBox_2_accepted()
{
    needInsert = true;
    name = ui->lineEditMaterial->text();
    description = ui->lineEditDescription->text();

    qDebug()<<"ok_perssed";
    this->close();

}
