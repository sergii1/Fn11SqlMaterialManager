#include "properyvaluechangedialog.h"
#include "ui_properyvaluechangedialog.h"

bool ProperyValueChangeDialog::needUpdate = false;
float ProperyValueChangeDialog::propertyValue = 0;

ProperyValueChangeDialog::ProperyValueChangeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProperyValueChangeDialog)
{
    ui->setupUi(this);
    ui->doubleSpinBox->setSingleStep(0.01);
    needUpdate = false;
    propertyValue = 0;
}

ProperyValueChangeDialog::~ProperyValueChangeDialog()
{
    delete ui;
}

float ProperyValueChangeDialog::getValue()
{
    return propertyValue;
}

void ProperyValueChangeDialog::on_pushButton_clicked()
{
    needUpdate = true;
    propertyValue = ui->doubleSpinBox->value();
    close();
}
