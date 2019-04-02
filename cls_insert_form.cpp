#include "cls_insert_form.h"

cls_insert_form::cls_insert_form(QWidget *parent):QDialog(parent){
    setModal(true);
    setWindowFlags (windowFlags() & ~Qt::WindowContextHelpButtonHint);
    submit = new QCommandLinkButton("Submit");
    lbl = new QLabel();
    layout = new QGridLayout();
    tbl_list = new QListWidget();
    tbl_list->addItems({
                       "Materials",
                       "Models",
                       "Properties",
                       "ModelComposition",
                       "MaterialsModels",
                       "MaterialsProperties"});

    connect(tbl_list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(element_is_selected(QListWidgetItem*)));
    connect(submit,SIGNAL(clicked()),this,SLOT(insert_data()));
    input_fields = new QVector<QLineEdit*>;
    columns = new QVector<QLabel*>;
    layout->addWidget(tbl_list,1,0,3,2);
    layout->addWidget(lbl,0,4,1,2);
   // layout->addWidget(columns,1,3,3,3);
    layout->addWidget(submit,3,3);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);

}


void cls_insert_form::element_is_selected(QListWidgetItem* p_item){

    for(int i = 0; i < input_fields->size();++i){
        layout->removeWidget((*input_fields)[i]);
        delete (*input_fields)[i];
    }
     input_fields->clear();

     for(int i = 0; i < columns->size();++i){
         layout->removeWidget((*columns)[i]);
         delete (*columns)[i];
     }
      columns->clear();

    //table == materialTypes
    if(p_item->text()=="LibMaterials"){

        this->lbl->setText(p_item->text());
        QSqlQuery query("select * from materialTypes",*local_db);
        QSqlRecord rec = query.record();
        for(int i = 0; i< rec.count();++i ){
            columns->append( new QLabel(rec.fieldName(i)));
            (*columns)[i]->setAlignment(Qt::AlignmentFlag::AlignCenter);
            (*columns)[i]->setFrameStyle(QFrame::Box);
            input_fields->append(new QLineEdit());
            layout->addWidget((*columns)[i],1,3+i,1,1);
            layout->addWidget((*input_fields)[i],2,3+i,1,1);
           // qDebug()<<rec.fieldName(i);
        }

    }

    //table == materials
    if(p_item->text()=="Materials"){

        this->lbl->setText(p_item->text());
        QStringList column_names;
        QSqlQuery query("select * from materials",*local_db);
        QSqlRecord rec = query.record();
        for(int i = 0; i< rec.count();++i ){
            columns->append( new QLabel(rec.fieldName(i)));
            (*columns)[i]->setAlignment(Qt::AlignmentFlag::AlignCenter);
            (*columns)[i]->setFrameStyle(QFrame::Box);
            input_fields->append(new QLineEdit());
            layout->addWidget((*columns)[i],1,3+i,1,1);
            layout->addWidget((*input_fields)[i],2,3+i,1,1);
           // qDebug()<<rec.fieldName(i);
        }

    }
    //table == Models
    if(p_item->text()=="Models")
    {
        this->lbl->setText(p_item->text());
        QSqlQuery query("select * from models",*local_db);
        QSqlRecord rec = query.record();
        for(int i = 0; i< rec.count();++i ){
            columns->append( new QLabel(rec.fieldName(i)));
            (*columns)[i]->setAlignment(Qt::AlignmentFlag::AlignCenter);
            (*columns)[i]->setFrameStyle(QFrame::Box);
            input_fields->append(new QLineEdit());
            layout->addWidget((*columns)[i],1,3+i,1,1);
            layout->addWidget((*input_fields)[i],2,3+i,1,1);
           // qDebug()<<rec.fieldName(i);
        }
    }
    if(p_item->text()== "Properties")
    {
        qDebug() << "Prop";
        this->lbl->setText(p_item->text());
        QSqlQuery query("select * from properties",*local_db);
        QSqlRecord rec = query.record();
        for(int i = 0; i< rec.count();++i ){
            columns->append( new QLabel(rec.fieldName(i)));
            (*columns)[i]->setAlignment(Qt::AlignmentFlag::AlignCenter);
            (*columns)[i]->setFrameStyle(QFrame::Box);
            input_fields->append(new QLineEdit());
            layout->addWidget((*columns)[i],1,3+i,1,1);
            layout->addWidget((*input_fields)[i],2,3+i,1,1);
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


        QSqlQuery query1("select * from models",*local_db);
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
            QSqlQuery query("select * from modelComposition",*local_db);
            QSqlRecord rec = query.record();
            columns->append(new QLabel(rec.fieldName(0)));
            columns->append(new QLabel(rec.fieldName(1)));
                (*columns)[0]->setAlignment(Qt::AlignmentFlag::AlignCenter);
                (*columns)[0]->setFrameStyle(QFrame::Box);
                (*columns)[1]->setAlignment(Qt::AlignmentFlag::AlignCenter);
                (*columns)[1]->setFrameStyle(QFrame::Box);
            layout->addWidget(modelComboBox,2,3,1,1);
            //input_fields->append(new QLineEdit());
            input_fields->append(new QLineEdit());
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


        QSqlQuery query1("select * from materials",*local_db);
        //qDebug() << query1.lastError();
            while(query1.next()){
                matComboBox->addItem(query1.value(0).toString());
                qDebug() << query1.value(0).toString();
            }
            modelComboBox = new QComboBox();


            QSqlQuery query2("select * from models",*local_db);
            //qDebug() << query1.lastError();
                while(query2.next()){
                    modelComboBox->addItem(query2.value(0).toString());
                    qDebug() << query2.value(0).toString();
                }
            QSqlQuery query("select * from materialsModels",*local_db);
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

        QSqlQuery query1("select * from materials",*local_db);
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
        QSqlQuery query("select * from propertyvaluescalar",*local_db);
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
        input_fields->append(new QLineEdit());
        layout->addWidget((*columns)[2],1,5,1,1);
        layout->addWidget((*input_fields)[0],2,5,1,1);
           // qDebug()<<rec.fieldName(i);
    }
}

void cls_insert_form::insert_data(){
    //table == materialTypes
    QString str;
    if(tbl_list->selectedItems()[0]->text()=="LibMaterials"){
         str = "insert into materialTypes(name, description) values('"+ (*input_fields)[0]->text() +"','"
                                                                            +(*input_fields)[1]->text()+"');";
        qDebug()<<'\n'<<str;

    }

    //table == materials
    if(tbl_list->selectedItems()[0]->text()=="Materials"){
         str = "insert into materials(id, description) values('"+ (*input_fields)[0]->text() +"','"
                                                                         + (*input_fields)[1]->text()+"');";
        qDebug()<<'\n'<<str;
    }

    //table == models
    if(tbl_list->selectedItems()[0]->text()=="Models"){
         str = "insert into models(name, description) values('"+ (*input_fields)[0]->text() +"','"
                                                                            +(*input_fields)[1]->text()+"');";
        qDebug()<<'\n'<<str;
    }

    //table == Properties
    if(tbl_list->selectedItems()[0]->text()=="Properties"){
         str = "insert into properties(name, description) values('"+ (*input_fields)[0]->text() +"','"
                                                                            +(*input_fields)[1]->text()+"');";
        qDebug()<<'\n'<<str;
    }

    //table == modelComposition
    if(tbl_list->selectedItems()[0]->text()=="ModelComposition"){
         str = "insert into modelComposition(models_name, properties_name) values('"+ modelComboBox->currentText() +"','"
                                                                            + propComboBox->currentText()+"');";
        qDebug()<<'\n'<<str;
    }

    //table == materialsmodels
    if(tbl_list->selectedItems()[0]->text()=="MaterialsModels"){
         str = "insert into materialsmodels(materials_name, models_name) values('"+matComboBox->currentText()+"','"
                                                                            + modelComboBox->currentText() +"');";
        qDebug()<<'\n'<<str;
    }

    //table == propertyValueScalar
    if(tbl_list->selectedItems()[0]->text()=="MaterialsProperties"){
         str = "insert into propertyValueScalar(materials_name, properties_name, value) values('"+
                                                                            matComboBox->currentText()+"','"
                                                                            +propComboBox->currentText()+"',"
                                                                            +(*input_fields)[0]->text()+");";
        qDebug()<<'\n'<<str;
    }
    if(local_db->exec(str).isActive())
        qDebug()<<"okey\n";
    qDebug() << "!!!" << local_db->lastError();
    emit need_update_table_view();
}

void cls_insert_form::closeEvent(QCloseEvent* p)
{
    qDebug() << "CLOSED";
    emit closed();
}

cls_insert_form::~cls_insert_form(){
    for(int i = 0; i < input_fields->size();++i){
        layout->removeWidget((*input_fields)[i]);
        delete (*input_fields)[i];
    }
     input_fields->clear();

     for(int i = 0; i < columns->size();++i){
         layout->removeWidget((*columns)[i]);
         delete (*columns)[i];
     }
      columns->clear();
      delete model;
      delete layout;
      delete tbl_list;
      delete lbl;
      delete columns;
      delete input_fields;
      delete submit;
}
