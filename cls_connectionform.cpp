#include "cls_connectionform.h"

cls_connectionForm::cls_connectionForm(QWidget *parent):QDialog(parent){


   // dck_formConnection = new QDockWidget;
    setModal(true);
    setWindowFlags (windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(("Подключение к БД"));
    nameDB = new QLineEdit();
    nameDB->setText("fn1132_2016");

    nameUser = new QLineEdit();
    nameUser->setText("student");

    Host = new QLineEdit();
    Host->setText("195.19.32.74");

    Port = new QLineEdit();
    Port->setText("5432");

    Password = new QLineEdit();
    Password->setText("bmstu");
    Password->setEchoMode(QLineEdit::Password);
    pbtnConnect = new QPushButton("Connect");

    //layout setup
    vLayout = new QVBoxLayout();
    vLayout->addWidget(new QLabel("DB name"));
    vLayout->addWidget(nameDB);
    vLayout->addWidget(new QLabel("User name"));
    vLayout->addWidget(nameUser);
    vLayout->addWidget(new QLabel("Host"));
    vLayout->addWidget(Host);
    vLayout->addWidget(new QLabel("Port"));
    vLayout->addWidget(Port);
    vLayout->addWidget(new QLabel("Password"));
    vLayout->addWidget(Password);
    vLayout->addWidget(pbtnConnect);
    setLayout(vLayout);
    resize(400,400);
}


