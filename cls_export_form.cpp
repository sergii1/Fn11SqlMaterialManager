#include "cls_export_form.h"

cls_export_form::cls_export_form(QStringList& lst, QWidget *parent) : QDialog(parent)
{
    setModal(true);
    setWindowFlags (windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("EXPORT");
    libList.addItems(lst);

    addLibMode.setText("добавить библиотеку");
    notAddLibMode.setText("использовать существующую");
    notAddLibMode.setChecked(true);
    layout.addWidget(&addLibMode,0,0,1,1);
    layout.addWidget(&notAddLibMode,0,1,1,1);
    stck.insertWidget(0,&libList);
    stck.insertWidget(1,&InputLib);
    layout.addWidget(&stck,1,0,1,2);
    pbntOK.setText("OK");
    layout.addWidget(&pbntOK,3,0,Qt::AlignCenter);
    setLayout(&layout);
    resize(475,150);

    connect(&addLibMode,SIGNAL(clicked()),this,SLOT(slot_ChooseMode()));
    connect(&notAddLibMode,SIGNAL(clicked()),this,SLOT(slot_ChooseMode()));
    connect(&pbntOK,SIGNAL(clicked()),this,SLOT(slot_pbntOkClicked()));
}

void cls_export_form::slot_ChooseMode(){

    if(dynamic_cast<QRadioButton*>(sender())->text()=="добавить библиотеку"){
        qDebug()<<"addLib";
        stck.setCurrentIndex(1);
    }
    else{
        qDebug()<<"old lib";
        stck.setCurrentIndex(0);
    }
}

void cls_export_form::slot_pbntOkClicked(){
    if(addLibMode.isChecked()&&!InputLib.text().isEmpty()){
        qDebug()<<InputLib.text();
        emit needAddLib(InputLib.text());
    }
    else
        qDebug()<<libList.currentText();
        emit needAddLib(libList.currentText());

}
