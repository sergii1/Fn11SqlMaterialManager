#include "cls_command_form.h"

cls_command_form::cls_command_form(QWidget* ptr, QWidget *parent):QWidget(parent){
    dock_CommandWdgt = new QDockWidget();
    commandText = new QTextEdit();
    command_res = new QLabel();
    command_res->setText("Result");
    submit = new QCommandLinkButton("Submit");
    rb_LocalDB = new QRadioButton("Локальная БД");
    rb_globalDB = new QRadioButton("Глобальная БД");
    rb_globalDB->setChecked(true);
    QWidget* wgt = new QWidget();
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(new QLabel("input cmd"),0,0,1,3);
    layout->addWidget(submit,0,3,1,1);
    layout->addWidget(commandText,1,0,2,7);
    layout->addWidget(command_res,4,0,2,2);
    layout->addWidget(rb_globalDB,1,8,1,3);
    layout->addWidget(rb_LocalDB,2,8,1,3);
    //layout->setColumnStretch(0,1);
    wgt -> setLayout(layout);
    dock_CommandWdgt->setWidget(wgt);
    connect(submit,SIGNAL(clicked()),ptr,SLOT(run_command()));
}

cls_command_form::~cls_command_form(){
    delete dock_CommandWdgt;
    delete commandText;
    delete command_res;
    delete submit;
    delete rb_globalDB;
    delete rb_LocalDB;
}
