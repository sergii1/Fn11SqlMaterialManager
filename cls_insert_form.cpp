#include "cls_insert_form.h"

cls_insert_form::cls_insert_form(QWidget *parent):QDialog(parent){
    setModal(true);
    setWindowFlags (windowFlags() & ~Qt::WindowContextHelpButtonHint);
    submit = new QCommandLinkButton("Submit");
    lbl = new QLabel();
    layout = new QGridLayout();
    tablesList = new QListWidget();
    tablesList->addItems({
                       "Materials",
                       "Models",
                       "Properties",
                       "ModelComposition",
                       "MaterialsModels",
                       "MaterialsProperties"});

    connect(tablesList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(elementIsSelected(QListWidgetItem*)));
    connect(submit,SIGNAL(clicked()),this,SLOT(insertData()));
    inputFields = new QVector<QLineEdit*>;
    columns = new QVector<QLabel*>;
    layout->addWidget(tablesList,1,0,3,2);
    layout->addWidget(lbl,0,4,1,2);
   // layout->addWidget(columns,1,3,3,3);
    layout->addWidget(submit,3,3);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);

}


void cls_insert_form::elementIsSelected(QListWidgetItem* p_item){

    for(int i = 0; i < inputFields->size();++i){
        layout->removeWidget((*inputFields)[i]);
        delete (*inputFields)[i];
    }
     inputFields->clear();

     for(int i = 0; i < columns->size();++i){
         layout->removeWidget((*columns)[i]);
         delete (*columns)[i];
     }
      columns->clear();

    //table == materialTypes
    if(p_item->text()=="LibMaterials"){

        this->lbl->setText(p_item->text());
        QSqlQuery query("select * from materialTypes",*localDB);
        QSqlRecord rec = query.record();
        for(int i = 0; i< rec.count();++i ){
            columns->append( new QLabel(rec.fieldName(i)));
            (*columns)[i]->setAlignment(Qt::AlignmentFlag::AlignCenter);
            (*columns)[i]->setFrameStyle(QFrame::Box);
            inputFields->append(new QLineEdit());
            layout->addWidget((*columns)[i],1,3+i,1,1);
            layout->addWidget((*inputFields)[i],2,3+i,1,1);
           // qDebug()<<rec.fieldName(i);
        }

    }

    //table == materials
    if(p_item->text()=="Materials"){

        this->lbl->setText(p_item->text());
        QStringList column_names;
        QSqlQuery query("select * from materials",*localDB);
        QSqlRecord rec = query.record();
        for(int i = 0; i< rec.count();++i ){
            columns->append( new QLabel(rec.fieldName(i)));
            (*columns)[i]->setAlignment(Qt::AlignmentFlag::AlignCenter);
            (*columns)[i]->setFrameStyle(QFrame::Box);
            inputFields->append(new QLineEdit());
            layout->addWidget((*columns)[i],1,3+i,1,1);
            layout->addWidget((*inputFields)[i],2,3+i,1,1);
           // qDebug()<<rec.fieldName(i);
        }

    }
    //table == Models
    if(p_item->text()=="Models")
    {
        this->lbl->setText(p_item->text());
        QSqlQuery query("select * from models",*localDB);
        QSqlRecord rec = query.record();
        for(int i = 0; i< rec.count();++i ){
            columns->append( new QLabel(rec.fieldName(i)));
            (*columns)[i]->setAlignment(Qt::AlignmentFlag::AlignCenter);
            (*columns)[i]->setFrameStyle(QFrame::Box);
            inputFields->append(new QLineEdit());
            layout->addWidget((*columns)[i],1,3+i,1,1);
            layout->addWidget((*inputFields)[i],2,3+i,1,1);
           // qDebug()<<rec.fieldName(i);
        }
    }
    if(p_item->text()== "Properties")
    {
        qDebug() << "Prop";
        this->lbl->setText(p_item->text());
        QSqlQuery query("select * from properties",*localDB);
        QSqlRecord rec = query.record();
        for(int i = 0; i< rec.count();++i ){
            columns->append( new QLabel(rec.fieldName(i)));
            (*columns)[i]->setAlignment(Qt::AlignmentFlag::AlignCenter);
            (*columns)[i]->setFrameStyle(QFrame::Box);
            inputFields->append(new QLineEdit());
            layout->addWidget((*columns)[i],1,3+i,1,1);
            layout->addWidget((*inputFields)[i],2,3+i,1,1);
            qDebug()<<rec.fieldName(i);
        }
    }
    //table == ModelComposition
    if(p_item->text()=="ModelComposition")
    {
        this->lbl->setText(p_item->text());
        QStringList column_names;
        modelComboBox = new QComboBox();
        propComboBox = new QComboBox();


        QSqlQuery query1("select * from models",*localDB);
        //qDebug() << query1.lastError();
            while(query1.next()){
                modelComboBox->addItem(query1.value(0).toString());
                qDebug() << query1.value(0).toString();
            }
        query1.exec("select * from properties");
            while(query1.next()){
                propComboBox->addItem(query1.value(0).toString());
                qDebug() << query1.value(0).toString();
            }
            QSqlQuery query("select * from modelComposition",*localDB);
            QSqlRecord rec = query.record();
            columns->append(new QLabel(rec.fieldName(0)));
            columns->append(new QLabel(rec.fieldName(1)));
                (*columns)[0]->setAlignment(Qt::AlignmentFlag::AlignCenter);
                (*columns)[0]->setFrameStyle(QFrame::Box);
                (*columns)[1]->setAlignment(Qt::AlignmentFlag::AlignCenter);
                (*columns)[1]->setFrameStyle(QFrame::Box);
            layout->addWidget(modelComboBox,2,3,1,1);
            //input_fields->append(new QLineEdit());
            inputFields->append(new QLineEdit());
            layout->addWidget((*columns)[0],1,3,1,1);
            layout->addWidget((*columns)[1],1,4,1,1);
            layout->addWidget(propComboBox,2,4,1,1);
           // qDebug()<<rec.fieldName(i);
    }
    //table == materialsmodels
    if(p_item->text()=="MaterialsModels"){
        this->lbl->setText(p_item->text());
        QStringList column_names;
        matComboBox = new QComboBox();


        QSqlQuery query1("select * from materials",*localDB);
        //qDebug() << query1.lastError();
            while(query1.next()){
                matComboBox->addItem(query1.value(0).toString());
                qDebug() << query1.value(0).toString();
            }
            modelComboBox = new QComboBox();


            QSqlQuery query2("select * from models",*localDB);
            //qDebug() << query1.lastError();
                while(query2.next()){
                    modelComboBox->addItem(query2.value(0).toString());
                    qDebug() << query2.value(0).toString();
                }
            QSqlQuery query("select * from materialsModels",*localDB);
            QSqlRecord rec = query.record();
            columns->append(new QLabel(rec.fieldName(0)));
            columns->append(new QLabel(rec.fieldName(1)));
                (*columns)[0]->setAlignment(Qt::AlignmentFlag::AlignCenter);
                (*columns)[0]->setFrameStyle(QFrame::Box);
                (*columns)[1]->setAlignment(Qt::AlignmentFlag::AlignCenter);
                (*columns)[1]->setFrameStyle(QFrame::Box);
            layout->addWidget(matComboBox,2,3,1,1);
            layout->addWidget(modelComboBox,2,4,1,1);
            //input_fields->append(new QLineEdit());
            layout->addWidget((*columns)[0],1,3,1,1);
            layout->addWidget((*columns)[1],1,4,1,1);
           // qDebug()<<rec.fieldName(i);
    }

    //table == propertyValueScalar
    if(p_item->text()=="MaterialsProperties"){
        matComboBox = new QComboBox();
        propComboBox = new QComboBox();

        QSqlQuery query1("select * from materials",*localDB);
        //qDebug() << query1.lastError();
            while(query1.next()){
                matComboBox->addItem(query1.value(0).toString());
                qDebug() << query1.value(0).toString();
            }
        query1.exec("select * from properties");
            while(query1.next()){
                propComboBox->addItem(query1.value(0).toString());
                qDebug() << query1.value(0).toString();
                }
        this->lbl->setText(p_item->text());
        QSqlQuery query("select * from propertyvaluescalar",*localDB);
        QSqlRecord rec = query.record();
        columns->append(new QLabel(rec.fieldName(0)));
        (*columns)[0]->setAlignment(Qt::AlignmentFlag::AlignCenter);
        (*columns)[0]->setFrameStyle(QFrame::Box);
        layout->addWidget(matComboBox,2,3,1,1);
        layout->addWidget((*columns)[0],1,3,1,1);
        //input_fields->append(new QLineEdit());
        columns->append(new QLabel(rec.fieldName(1)));
        (*columns)[1]->setAlignment(Qt::AlignmentFlag::AlignCenter);
        (*columns)[1]->setFrameStyle(QFrame::Box);
        layout->addWidget(propComboBox,2,4,1,1);
        //input_fields->append(new QLineEdit());
        layout->addWidget((*columns)[1],1,4,1,1);
        columns->append( new QLabel(rec.fieldName(2)));
        (*columns)[2]->setAlignment(Qt::AlignmentFlag::AlignCenter);
        (*columns)[2]->setFrameStyle(QFrame::Box);
        inputFields->append(new QLineEdit());
        layout->addWidget((*columns)[2],1,5,1,1);
        layout->addWidget((*inputFields)[0],2,5,1,1);
           // qDebug()<<rec.fieldName(i);
    }
}

void cls_insert_form::insertData(){
    //table == materialTypes
    QString str;
    if(tablesList->selectedItems()[0]->text()=="LibMaterials"){
         str = "insert into materialTypes(name, description) values('"+ (*inputFields)[0]->text() +"','"
                                                                            +(*inputFields)[1]->text()+"');";
        qDebug()<<'\n'<<str;

    }

    //table == materials
    if(tablesList->selectedItems()[0]->text()=="Materials"){
         str = "insert into materials(id, description) values('"+ (*inputFields)[0]->text() +"','"
                                                                         + (*inputFields)[1]->text()+"');";
        qDebug()<<'\n'<<str;
    }

    //table == models
    if(tablesList->selectedItems()[0]->text()=="Models"){
         str = "insert into models(name, description) values('"+ (*inputFields)[0]->text() +"','"
                                                                            +(*inputFields)[1]->text()+"');";
        qDebug()<<'\n'<<str;
    }

    //table == Properties
    if(tablesList->selectedItems()[0]->text()=="Properties"){
         str = "insert into properties(name, description) values('"+ (*inputFields)[0]->text() +"','"
                                                                            +(*inputFields)[1]->text()+"');";
        qDebug()<<'\n'<<str;
    }

    //table == modelComposition
    if(tablesList->selectedItems()[0]->text()=="ModelComposition"){
         str = "insert into modelComposition(models_name, properties_name) values('"+ modelComboBox->currentText() +"','"
                                                                            + propComboBox->currentText()+"');";
        qDebug()<<'\n'<<str;
    }

    //table == materialsmodels
    if(tablesList->selectedItems()[0]->text()=="MaterialsModels"){
         str = "insert into materialsmodels(materials_name, models_name) values('"+matComboBox->currentText()+"','"
                                                                            + modelComboBox->currentText() +"');";
        qDebug()<<'\n'<<str;
    }

    //table == propertyValueScalar
    if(tablesList->selectedItems()[0]->text()=="MaterialsProperties"){
         str = "insert into propertyValueScalar(materials_name, properties_name, value) values('"+
                                                                            matComboBox->currentText()+"','"
                                                                            +propComboBox->currentText()+"',"
                                                                            +(*inputFields)[0]->text()+");";
        qDebug()<<'\n'<<str;
    }
    if(localDB->exec(str).isActive())
        qDebug()<<"okey\n";
    qDebug() << "!!!" << localDB->lastError();
    emit needUpdateTableView();
}

void cls_insert_form::closeEvent(QCloseEvent* p)
{
    qDebug() << "CLOSED";
    emit closed();
}

cls_insert_form::~cls_insert_form(){
    for(int i = 0; i < inputFields->size();++i){
        layout->removeWidget((*inputFields)[i]);
        delete (*inputFields)[i];
    }
     inputFields->clear();

     for(int i = 0; i < columns->size();++i){
         layout->removeWidget((*columns)[i]);
         delete (*columns)[i];
     }
      columns->clear();
      delete model;
      delete layout;
      delete tablesList;
      delete lbl;
      delete columns;
      delete inputFields;
      delete submit;
}
