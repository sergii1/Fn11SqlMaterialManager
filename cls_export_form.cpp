#include "cls_export_form.h"

cls_export_form::cls_export_form(QStringList& lst, QWidget *parent) : QDialog(parent)
{
    setModal(true);
    setWindowFlags (windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("EXPORT");
    //VLayout.addWidget(new QLabel("В какую библиотеку добавить новые материалы?"));
    //InputLib.setFixedSize(250,50);
   //VLayout.addWidget(&InputLib);
    libList.addItems(lst);

    add_libMode.setText("добавить библиотеку");
    not_add_libMode.setText("использовать существующую");
    not_add_libMode.setChecked(true);
    layout.addWidget(&add_libMode,0,0,1,1);
    layout.addWidget(&not_add_libMode,0,1,1,1);
    stck.insertWidget(0,&libList);
    stck.insertWidget(1,&InputLib);
    layout.addWidget(&stck,1,0,1,2);
    pbntOK.setText("OK");
    layout.addWidget(&pbntOK,3,0,Qt::AlignCenter);
    setLayout(&layout);
    resize(475,150);

    connect(&add_libMode,SIGNAL(clicked()),this,SLOT(slot_choose_mode()));
    connect(&not_add_libMode,SIGNAL(clicked()),this,SLOT(slot_choose_mode()));
    connect(&pbntOK,SIGNAL(clicked()),this,SLOT(slot_pbntOK_clicked()));
}

void cls_export_form::slot_choose_mode(){

    if(dynamic_cast<QRadioButton*>(sender())->text()=="добавить библиотеку"){
        qDebug()<<"addLib";
        stck.setCurrentIndex(1);
    }
    else{
        qDebug()<<"old lib";
        stck.setCurrentIndex(0);
    }
}

void cls_export_form::slot_pbntOK_clicked(){
    if(add_libMode.isChecked()&&!InputLib.text().isEmpty()){
        qDebug()<<InputLib.text();
        emit need_AddLib(InputLib.text());
    }
    else
        qDebug()<<libList.currentText();
        emit need_AddLib(libList.currentText());

}
