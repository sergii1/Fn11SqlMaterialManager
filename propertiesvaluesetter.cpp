#include "propertiesvaluesetter.h"
#include "ui_propertiesvaluesetter.h"

bool PropertiesValueSetter::needSetValue = false;
QString PropertiesValueSetter::field1 = "";
QString PropertiesValueSetter::field2 = "";
double PropertiesValueSetter::value = 0;

PropertiesValueSetter::PropertiesValueSetter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropertiesValueSetter)
{
    ui->setupUi(this);
    PropertiesValueSetter::needSetValue = false;
    PropertiesValueSetter::field1 = "";
    PropertiesValueSetter::field2 = "";
    PropertiesValueSetter::value = 0;
}

QComboBox* PropertiesValueSetter::getComboBox1(){
    return ui->comboBox_2;
}

QLabel* PropertiesValueSetter::getLabel(){
    return ui->label_4;
}

QDoubleSpinBox* PropertiesValueSetter::getSpinBox(){
    return ui->doubleSpinBox;
}

QString PropertiesValueSetter::getField1(){
    return field1;
}

QString PropertiesValueSetter:: getField2(){
    return field2;
}

double PropertiesValueSetter::getValue(){
    return value;
}

PropertiesValueSetter::~PropertiesValueSetter()
{
    delete ui;
}

void PropertiesValueSetter::on_pushButton_clicked()
{
    PropertiesValueSetter::needSetValue = true;
    PropertiesValueSetter::field1 = ui->label_4->text();
    PropertiesValueSetter::field2 = ui->comboBox_2->currentText();
    PropertiesValueSetter::value = ui->doubleSpinBox->value();
    this->close();
}
