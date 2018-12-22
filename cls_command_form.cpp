#include "cls_command_form.h"

cls_command_form::cls_command_form(QWidget* ptr, QWidget *parent):QWidget(parent){
    dck_command_wdgt = new QDockWidget();
    command_text = new QTextEdit();
    command_res = new QLabel();
    command_res->setText("Result");
    submit = new QCommandLinkButton("Submit");
    rb_localDb = new QRadioButton("Локальная БД");
    rb_globalDb = new QRadioButton("Глобальная БД");
    rb_globalDb->setChecked(true);
    QWidget* wgt = new QWidget();
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(new QLabel("input cmd"),0,0,1,3);
    layout->addWidget(submit,0,3,1,1);
    layout->addWidget(command_text,1,0,2,7);
    layout->addWidget(command_res,4,0,2,2);
    layout->addWidget(rb_globalDb,1,8,1,3);
    layout->addWidget(rb_localDb,2,8,1,3);
    //layout->setColumnStretch(0,1);
    wgt -> setLayout(layout);
    dck_command_wdgt->setWidget(wgt);
    connect(submit,SIGNAL(clicked()),ptr,SLOT(run_command()));
}

cls_command_form::~cls_command_form(){
    delete dck_command_wdgt;
    delete command_text;
    delete command_res;
    delete submit;
    delete rb_globalDb;
    delete rb_localDb;
}
