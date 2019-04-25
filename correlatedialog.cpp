#include "correlatedialog.h"
#include "ui_correlatedialog.h"

QString CorrelateDialog::field1 = "";
QString CorrelateDialog::field2 = "";
bool CorrelateDialog::needCorrelate = false;

CorrelateDialog::CorrelateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CorrelateDialog)
{
    ui->setupUi(this);
    CorrelateDialog::needCorrelate=false;
    CorrelateDialog::field1="";
    CorrelateDialog::field2="";
}

QLabel* CorrelateDialog::getLabel1(){
    return ui->label;
}

QLabel* CorrelateDialog::getLabel2(){
    return ui->label_2;
}

QLabel* CorrelateDialog::getLabel3(){
    return ui->label_3;
}

QComboBox* CorrelateDialog::getComboBox(){
    return ui->comboBox_2;
}

QString CorrelateDialog::getField1(){
    return CorrelateDialog::field1;
}

QString CorrelateDialog::getField2(){
    return CorrelateDialog::field2;
}

CorrelateDialog::~CorrelateDialog()
{
    delete ui;
}

void CorrelateDialog::on_pushButton_clicked()
{
    CorrelateDialog::needCorrelate=true;
    CorrelateDialog::field1 = ui->label_3->text();
    CorrelateDialog::field2 = ui->comboBox_2->currentText();
    this->close();
}
