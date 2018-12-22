#include "api.h"
#include "ui_api.h"

api::api(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::api)
{
    ui->setupUi(this);
}

api::~api()
{
    delete ui;
}
