#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QSqlDatabase* p_db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    db = p_db;
    ui->rb_global->setChecked(true);
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}




void ConnectionDialog::on_rb_global_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void ConnectionDialog::on_rb_local_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

QPushButton* ConnectionDialog::get_btn_globalConnect(){
    return ui->btn_globalConnect;
}

QString ConnectionDialog::getNameDB(){
    return ui->line_dbName->text();
}

QString ConnectionDialog::getUserName(){
    return ui->line_userName->text();
}

QString ConnectionDialog::getHost(){
    return ui->line_host->text();
}

int ConnectionDialog::getPort(){
    return ui->line_port->text().toInt();
}

QString ConnectionDialog::getPassword(){
    return ui->line_password->text();
}


