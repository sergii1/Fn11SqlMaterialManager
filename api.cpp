#include "api.h"
#include "ui_api.h"
#include <algorithm>
#include <QSize>

API::API(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::API)
{
    //setStyle(QStyleFactory::create("Fusion"));
    setWindowModality(Qt::WindowModal);
    setWindowIcon(QIcon(":new/tools/resources/sqldevops.png"));
    setStyleSheet("centralWidget {background: yellow;width: 10px; height: 10px; / when horizontal */}centralWidget:hover {background: red;}");
    ui->setupUi(this);
    m_Layout = new QGridLayout;
    flagImport=false;
    flagSQLQuery = false;

    command_form = new cls_command_form();

    Lib = new QTreeWidget();
    Mat = new QTableView();
    Model = new QTableView();
    Properties = new QTableView();
    tabLib = new QDockWidget;
    tabLib->setWindowTitle("Библиотеки материалов");
    tabLib->setAllowedAreas(Qt::LeftDockWidgetArea);
    tabLib->setFixedWidth(335);
    tabLib->setFeatures(QDockWidget::DockWidgetMovable);
    //this->addDockWidget(Qt::LeftDockWidgetArea, tabLib);

    tabMat = new QDockWidget;
    tabMat->setWindowTitle("Материалы");
    tabMat->setAllowedAreas(Qt::LeftDockWidgetArea);
    tabMat->setFixedWidth(395);
    tabMat->setFeatures(QDockWidget::DockWidgetMovable);
   // this->addDockWidget(Qt::LeftDockWidgetArea, tabMat);

    tabModel = new QDockWidget;
    tabModel->setWindowTitle("Модели материала");
    tabModel->setAllowedAreas(Qt::LeftDockWidgetArea);
    tabModel->setFixedWidth(395);
    tabModel->setFeatures(QDockWidget::DockWidgetMovable);
    //this->addDockWidget(Qt::LeftDockWidgetArea, tabModel);

    tabProperties = new QDockWidget;
    tabProperties->setWindowTitle("Свойства материала");
    tabProperties->setAllowedAreas(Qt::LeftDockWidgetArea);
    tabProperties->setFixedWidth(335);
    tabProperties->setFeatures(QDockWidget::DockWidgetMovable);
   // setCentralWidget(tabProperties);
//  this->addDockWidget(Qt::TopDockWidgetArea, tabProperties);

    l_Mat = new QTableView();
    l_Model = new QTableView();

    l_tabMat = new QDockWidget;
    l_tabMat->setWindowTitle("Материалы");
    l_tabMat->setAllowedAreas(Qt::RightDockWidgetArea);
    l_tabMat->setFixedWidth(395);
    l_tabMat->setFeatures(QDockWidget::DockWidgetMovable);
    //this->addDockWidget(Qt::RightDockWidgetArea, l_tabMat);

    l_tabModel = new QDockWidget;
    l_tabModel->setWindowTitle("Модели материала");
    l_tabModel->setAllowedAreas(Qt::RightDockWidgetArea);
    l_tabModel->setFixedWidth(395);
    l_tabModel->setFeatures(QDockWidget::DockWidgetMovable);
   // this->addDockWidget(Qt::RightDockWidgetArea, l_tabModel);

    QWidget* body = new QWidget;
    body->setLayout(m_Layout);
    setCentralWidget(body);

    QSplitter* vSplit1 = new QSplitter(Qt::Horizontal);
    vSplit1->addWidget(tabMat);
    vSplit1->addWidget(tabModel);


//    QSplitter* vSplit2 = new QSplitter(Qt::Vertical);
//    vSplit2->addWidget(l_tabMat);
//    vSplit2->addWidget(l_tabModel);

    m_Layout->addWidget(tabLib,0,0,2,1);
    m_Layout->addWidget(tabMat,0,1,1,1);
    m_Layout->addWidget(tabModel,1,1,1,1);
 // m_Layout->addWidget(vSplit1,0,1,2,1);
    m_Layout->addWidget(tabProperties,0,2,1,1,Qt::AlignHCenter);
    m_Layout->addWidget(l_tabMat,0,3,1,1);
    m_Layout->addWidget(l_tabModel,1,3,1,1);

    QToolBar* ptb = new QToolBar("Панель инструментов");
//    ptb->setStyleSheet("background-color:darkgray;");
    QMenu* pmnuConnect = new QMenu("&Подключение");
       QAction* pactConnect = new QAction ("Подключение к серверу...", nullptr) ;
       pactConnect -> setText ("&Подключение к серверу...");
       pactConnect -> setShortcut ( QKeySequence ("CTRL+O"));
       pactConnect->setIcon (QPixmap(":new/tools/resources/addDB.png"));
       ptb->addAction(pactConnect);
       pmnuConnect->addAction(pactConnect);
       connect(pactConnect, SIGNAL(triggered(bool)) , this, SLOT(slotFormConnection()));
    menuBar()->addMenu(pmnuConnect);
    ptb->addSeparator();
    QMenu* pmnuTools = new QMenu("Инструменты");
       pactImport = new QAction ("Импорт", nullptr) ;
       pactImport -> setText ("&Импорт");
       pactImport -> setShortcut ( QKeySequence ("CTRL+I"));
       pactImport->setIcon (QPixmap(":new/tools/resources/import.png"));
       pactImport->setEnabled(false);
       ptb->addAction(pactImport);
    pmnuTools->addAction(pactImport);
       pactExport = new QAction ("Экспорт", nullptr) ;
       pactExport -> setText ("&Экспорт");
       pactExport -> setShortcut ( QKeySequence ("CTRL+E"));
       pactExport->setIcon (QPixmap(":new/tools/resources/export.png"));
       ptb->addAction(pactExport);
//       pactExport->setEnabled(false);
    pmnuTools->addAction(pactExport);
        pactAddData = new QAction ("Добавить данные", nullptr) ;
        pactAddData -> setText ("&Добавить данные");
//        pactAddData->setEnabled(false);
    pmnuTools->addAction(pactAddData);
        pactDeleteMat = new QAction ("Удалить материал", nullptr) ;
        pactDeleteMat -> setText ("&Удалить материал");
//        pactDeleteMat->setEnabled(false);
    pmnuTools->addAction(pactDeleteMat);
        pactDeleteModel = new QAction ("Удалить модель", nullptr) ;
        pactDeleteModel -> setText ("&Удалить модель");
//        pactDeleteModel->setEnabled(false);
    pmnuTools->addAction(pactDeleteMat);
        pactSQLQuery = new QAction ("Выполнить SQL запрос", nullptr) ;
        pactSQLQuery -> setText ("Выполнить SQL запрос");
        pactSQLQuery -> setIcon(QIcon(":resources/SQL.png"));
        ptb->addAction(pactSQLQuery);
//        pactSQLQuery->setEnabled(false);
    pmnuTools->addAction(pactSQLQuery);
    menuBar()->addMenu(pmnuTools);
    addToolBar(Qt::TopToolBarArea, ptb);
    QMenu* pmnuFAQ = new QMenu("Справка");
    pmnuFAQ->addAction("О программе", this, [](){QMessageBox::about(nullptr, "О программе",
                                                                             "Осман Шамшидов (ФН11-32)\nЧепурной Сергий (ФН11-32)");});
    menuBar()->addMenu(pmnuFAQ);
    //pbtnImport->setFixedSize(QSize(20,20));
    //pbtnExport->setFixedSize(QSize(20,20));
//    m_Layout = new QGridLayout();
//    widget->setLayout(m_Layout);
//    setCentralWidget(widget);

    local_db = QSqlDatabase::addDatabase("QSQLITE", "Local");
    global_db = QSqlDatabase::addDatabase("QPSQL");
    insert_form = new cls_insert_form();
    insert_form->global_db = &global_db;
    insert_form->local_db = &local_db;
//    this->addDockWidget(Qt::TopDockWidgetArea,insert_form->dck_indert_form);

    Mat->verticalHeader()->setDefaultSectionSize(28);
    Model->verticalHeader()->setDefaultSectionSize(28);
    Properties->verticalHeader()->setDefaultSectionSize(28);
    l_Mat->verticalHeader()->setDefaultSectionSize(28);
    l_Model->verticalHeader()->setDefaultSectionSize(28);

    connect(this,SIGNAL(need_update_table_view()),this,SLOT(update_table_view()));
    connect(pactImport, SIGNAL(triggered(bool)), this, SLOT(slotImport()));
    connect(pactExport, SIGNAL(triggered(bool)), this, SLOT(slotExport()));
    connect(pactAddData, SIGNAL(triggered(bool)), this, SLOT(slotShowInsertForm()));
    connect(pactDeleteMat, SIGNAL(triggered(bool)), this, SLOT(slotDeleteMat()));
    connect(pactDeleteModel, SIGNAL(triggered(bool)), this, SLOT(slotDeleteModel()));
    connect(pactSQLQuery, SIGNAL(triggered(bool)), this, SLOT(slotSQLQuery()));
   // connect(this,SIGNAL(connection_is_created()),SLOT(createListOfGlobalTable()));
    connect(insert_form,SIGNAL(need_update_table_view()),this,SLOT(update_table_view()));

//    tabLib->hide();
//    tabMat->hide();
//    tabModel->hide();
//    tabProperties->hide();
//    l_tabMat->hide();
//    l_tabModel->hide();
    statusBar()->showMessage("Подключите БД", 10000);
}

void API::slotFormConnection()
{
    connectionForm = new cls_connectionForm();
    connectionForm->setWindowIcon(QIcon(":new/tools/resources/addDB.png"));
    connect(connectionForm->pbtnConnect,SIGNAL(clicked()), this, SLOT(slotConnection()));
   // connectionForm->setWindowTitle(("Подключение к БД"));
    //connectionForm->dck_formConnection->show();
    //this->addDockWidget(Qt::BottomDockWidgetArea,connectionForm->dck_formConnection);
    connectionForm->show();
}

void API::slotConnection()
{
    if(createConnection()){
        connectionForm->close();
        emit connection_is_created();
    }

}

bool API::createConnection()
{
 //   qDebug()<<"create connection slot\n";
    local_db.open();
    global_db.setDatabaseName(connectionForm->nameDB->text());
    global_db.setUserName(connectionForm->nameUser->text());
    global_db.setHostName(connectionForm->Host->text());
    global_db.setPort(connectionForm->Port->text().toInt());
    global_db.setPassword(connectionForm->Password->text());
    if (!global_db.open()) {
        qDebug()<<"db not open";
        QMessageBox* pmbx =
         new QMessageBox(QMessageBox::Warning,
         "Warning",
         "Ошибка открытия БД, попробуйте снова");
        pmbx->show();
        statusBar()->showMessage("Ошибка открытия БД", 3000);
        statusBar()->showMessage("Ошибка подключения", 3000);
     }

    //view->setEditTriggers(QTableView::NoEditTriggers);
//    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery(global_db);
    query->exec("SELECT * FROM materialTypes;");
//    QString str ="SELECT * FROM materialTypes;";
//    model->setQuery(str, global_db);
    QStringList lst;
    lst << "Name" << "Description";
    Lib->setHeaderLabels(lst);
    Lib->clear();
    while(query->next())
    {
        QTreeWidgetItem *ptwgItem = new QTreeWidgetItem(Lib);
        ptwgItem->setText(0,query->value(0).toString());
        QTreeWidgetItem *ptwgItemDir = new QTreeWidgetItem(ptwgItem);
        ptwgItemDir->setText(1, query->value(1).toString());
    }
    tabLib->setWidget(Lib);
    tabLib->show();
    tabMat->show();
    tabModel->show();
    tabProperties->show();
    l_tabMat->show();
    l_tabModel->show();
    connect(Lib, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSelectMat()));
    this->insert_form->global_db=&global_db;
    this->insert_form->local_db=&local_db;
    setColumnWidth();
    pactSQLQuery->setEnabled(true);
    statusBar()->showMessage("Готово", 3000);
    return true;
}

void API::slotSelectMat()
{
    //view->setEditTriggers(QTableView::NoEditTriggers);
    QSqlQueryModel* model = new QSqlQueryModel();
    //QSqlTableModel* m = new QSqlTableModel();
    QString nameMaterial = Lib->currentItem()->text(0);
    QString str = "SELECT name, description FROM materials WHERE  materialTypes_name ='"+ nameMaterial +"';";
    model->setQuery(str, global_db);
    Mat->setModel(model);
    tabMat->setWidget(Mat);
    connect(Mat, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSelectModel()));
    setColumnWidth();
    pactImport->setEnabled(false);
}

QString nameMaterial;

void API::slotSelectModel()
{
    //view->setEditTriggers(QTableView::NoEditTriggers);
        QSqlQueryModel* model = new QSqlQueryModel();
        nameMaterial = Mat->model()->data(Mat->model()->index(Mat->currentIndex().row(), 0)).toString();
        QString str = "SELECT models_name, description FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';";
        global_db.open();
        model->setQuery(str, global_db);
        Model->setModel(model);
        tabModel->setWidget(Model);
        connect(Model, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSelectProperties()));
        setColumnWidth();
        pactImport->setEnabled(false);
}

void API::slotSelectProperties()
{
    QString nameModel =Model->model()->data(Model->model()->index(Model->currentIndex().row(), 0)).toString();
    QSqlQueryModel* model = new QSqlQueryModel();
    QString str = "select  DISTINCT properties_name as property, value from  (select materials_name, models_name , propertyValueScalar.properties_name, value from  propertyValueScalar join modelComposition  on propertyValueScalar.properties_name = modelComposition.properties_name )  as allProp  join materialsModels on  allProp.materials_name = materialsModels.materials_name and allProp.models_name = materialsModels.models_name where materialsModels.models_name = '" + nameModel + "' and materialsModels.materials_name = '" + nameMaterial +"';";
    //QString str = "SELECT properties_name, value FROM (SELECT materials_name, models_name , properties_name, value, models_name FROM propertyValueScalar JOIN modelComposition ON propertyValueScalar.properties_name = modelComposition.properties_name) join materialsModels on allProp.materials_name = materialsModels.materials_name and  allProp.models_name = materialsModels.models_name where materialsModels.models_name = 'IsoElst' and materialsModels.materials_name = 'carbon';";
    model->setQuery(str, global_db);
    Properties->setModel(model);
    tabProperties->setWidget(Properties);
    pactImport->setEnabled(true);
    setColumnWidth();
}

void API::slotImport()
{
    global_db.close();
       QSqlQuery* localQuery;
//    QString str = "CREATE TABLE materialTypes(name text primary key, description text);";
//    localQuery->exec(str);
    QSqlQuery* globalQuery;
    if (global_db.open())
        globalQuery = new QSqlQuery(global_db);
    else return;
    localQuery = new QSqlQuery(local_db);
//    globalQuery->exec("SELECT * FROM materialTypes;");
//    while(globalQuery->next())
//    {
//        str = "INSERT INTO materialTypes(name, description) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
//        localQuery->exec(str);
//    }
//    QString nameTypeMaterial = Lib->model()->data(Lib->model()->index(Lib->currentIndex().row(), 0)).toString();
    QString nameMaterial = Mat->model()->data(Mat->model()->index(Mat->currentIndex().row(), 0)).toString();
    QString nameModel = Model->model()->data(Model->model()->index(Model->currentIndex().row(), 0)).toString();
    QString str;
    str = "PRAGMA foreign_keys = on";
    localQuery->exec(str);
    qDebug() << str;
    qDebug() << localQuery->lastError();
    str = "CREATE TABLE materials(name text primary key, description text);";
    localQuery->exec(str);
    qDebug() << str;
    qDebug() << localQuery->lastError();
    qDebug() << nameMaterial;
    globalQuery->exec("SELECT * FROM materials WHERE name ='"+ nameMaterial +"';");

    while(globalQuery->next())
    {
        str = "INSERT INTO materials(name, description) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(2).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }
    str = "create table models(name text primary key, description text);";
    localQuery->exec(str);
    qDebug() << str;
    qDebug() << localQuery->lastError();
    globalQuery->exec("SELECT * FROM models;");
    while(globalQuery->next())
    {
        str = "INSERT INTO models(name, description) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }
    str = "create table properties (name text primary key, description text);";
    localQuery->exec(str);
    qDebug() << str;
    qDebug() << localQuery->lastError();

    globalQuery->exec("SELECT * FROM properties;");
    while(globalQuery->next())
    {
        str = "INSERT INTO properties(name) values ('" + globalQuery->value(0).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }
    str = "create table modelComposition(models_name text references models(name) ON DELETE CASCADE, properties_name text  references properties(name));";
    localQuery->exec(str);
    qDebug() << str;
    qDebug() << localQuery->lastError();
    globalQuery->exec("SELECT * FROM modelComposition;");
    while(globalQuery->next())
    {
        str = "INSERT INTO modelComposition(models_name, properties_name) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }
    str = "CREATE TABLE materialsModels(materials_name text references materials(name) ON DELETE CASCADE, models_name text references models(name) ON DELETE CASCADE,  primary key(materials_name, models_name));";
    localQuery->exec(str);
    qDebug() << str;
    qDebug() << localQuery->lastError();
    globalQuery->exec("SELECT * FROM materialsModels WHERE models_name = '" + nameModel + "' AND materials_name = '" + nameMaterial + "';");
    while(globalQuery->next())
    {
        str = "INSERT INTO materialsModels(materials_name, models_name) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }
    str ="SELECT * FROM materialTypes;";

    str = "CREATE TABLE propertyValueScalar(materials_name text references materials(name) ON DELETE CASCADE, properties_name text, value float not null, primary key(materials_name, properties_name));";
    localQuery->exec(str);
    qDebug() << str;
    qDebug() << localQuery->lastError();
    globalQuery->exec("SELECT * FROM propertyValueScalar WHERE materials_name = '" + nameMaterial + "';");
    while(globalQuery->next())
    {
        str = "INSERT INTO propertyValueScalar(materials_name, properties_name, value) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "', '" + globalQuery->value(2).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }
    QSqlQueryModel* model = new QSqlQueryModel();
    str ="SELECT name, description  FROM materials;";
    model->setQuery(str, local_db);
    l_Mat->setModel(model);
    l_tabMat->setWidget(l_Mat);
    pactExport->setEnabled(true);
    pactAddData->setEnabled(true);
    pactDeleteMat->setEnabled(true);
    pactDeleteModel->setEnabled(true);
    connect(l_Mat, SIGNAL(clicked(QModelIndex)), this, SLOT(slotLocalSelectModel()));
    flagImport = true;
    setColumnWidth();
    statusBar()->showMessage("Успешно", 3000);
}

void API::slotExport()
{

    QStringList lst;
    QSqlQuery query("select name from materialTypes",global_db);
    if(query.isActive()){
        while (query.next())
                   lst<<query.value(0).toString();

    export_form = new cls_export_form(lst);
    connect(export_form, SIGNAL(need_AddLib(const QString&)), this, SLOT(slotAddLib(const QString &)));
    export_form->show();
    //local_db.close();
    QSqlQuery* globalQuery;
    if(global_db.open())
        globalQuery = new QSqlQuery(global_db);
    else return;
    }
    setColumnWidth();
}

void API::slotAddLib(const QString & newLib)
{
   export_form->close();
   QSqlQuery* globalQuery;
   if(global_db.open())
        globalQuery = new QSqlQuery(global_db);
   //newLib = InputLib->toPlainText();
   QString str = "INSERT INTO materialTypes(name) VALUES ('" + newLib +"');";
   globalQuery->exec(str);
   qDebug() << globalQuery->lastError();
   QSqlQueryModel* model = new QSqlQueryModel();
   QSqlQuery* localQuery = new QSqlQuery(local_db);
   localQuery->exec("SELECT * FROM materials;");
   while(localQuery->next())
   {
       qDebug() << localQuery->value(0).toString();
       str = "INSERT INTO materials(name, materialTypes_name, description ) VALUES ('" + localQuery->value(0).toString() + "', '" + newLib + "', '" + localQuery->value(2).toString() +"');";
       globalQuery->exec(str);
   }
   localQuery->exec("SELECT * FROM models;");
   while(localQuery->next())
   {
       str = "INSERT INTO models(name, description) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "');";
       globalQuery->exec(str);
   }

   localQuery->exec("SELECT * FROM properties;");
   while(localQuery->next())
   {
       str = "INSERT INTO properties(name) values ('" + localQuery->value(0).toString() + "');";
       globalQuery->exec(str);
       qDebug() << str;
       qDebug() << globalQuery->lastError();
   }

   localQuery->exec("SELECT * FROM modelComposition;");
   while(localQuery->next())
   {
       str = "INSERT INTO modelComposition(models_name, properties_name) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "');";
       globalQuery->exec(str);
   }
   localQuery->exec("SELECT * FROM materialsModels;");
   while(localQuery->next())
   {
       qDebug() << localQuery->value(0).toString();
       qDebug() << localQuery->value(1).toString();
       str = "INSERT INTO materialsModels(materials_name, models_name) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "');";
       globalQuery->exec(str);
       qDebug() << globalQuery->lastError();
   }

   localQuery->exec("SELECT * FROM propertyValueScalar;");
   while(localQuery->next())
   {
       str = "INSERT INTO propertyValueScalar(materials_name, properties_name, value) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "', '" + localQuery->value(2).toString() + "');";
       globalQuery->exec(str);
       qDebug() << globalQuery->lastError();
   }
   QSqlQuery* query = new QSqlQuery(global_db);
   query->exec("SELECT * FROM materialTypes;");
   Lib->clear();
   while(query->next())
   {
       QTreeWidgetItem *ptwgItem = new QTreeWidgetItem(Lib);
       ptwgItem->setText(0,query->value(0).toString());
       QTreeWidgetItem *ptwgItemDir = new QTreeWidgetItem(ptwgItem);
       ptwgItemDir->setText(1, query->value(1).toString());
   }
   tabLib->setWidget(Lib);

    setColumnWidth();
    statusBar()->showMessage("Успешно", 3000);
}

void API::slotLocalSelectModel()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    nameMaterial = l_Mat->model()->data(l_Mat->model()->index(l_Mat->currentIndex().row(), 0)).toString();
    QString str = "SELECT models_name, description FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';";
    model->setQuery(str, local_db);
    qDebug() << model->lastError();
    l_Model->setModel(model);
    l_tabModel->setWidget(l_Model);
    connect(l_Model, SIGNAL(clicked(QModelIndex)), this, SLOT(slotLocalSelectProperties()));

    setColumnWidth();
}

void API::slotLocalSelectProperties()
{
    QString nameModel =l_Model->model()->data(l_Model->model()->index(l_Model->currentIndex().row(), 0)).toString();
    QSqlQueryModel* model = new QSqlQueryModel();
    QString str = "select DISTINCT properties_name as property, value from  (select materials_name, models_name , propertyValueScalar.properties_name, value from  propertyValueScalar join modelComposition  on propertyValueScalar.properties_name = modelComposition.properties_name )  as allProp  join materialsModels on  allProp.materials_name = materialsModels.materials_name and allProp.models_name = materialsModels.models_name where materialsModels.models_name = '" + nameModel + "' and materialsModels.materials_name = '" + nameMaterial +"';";
    //QString str = "SELECT properties_name, value FROM (SELECT materials_name, models_name , properties_name, value, models_name FROM propertyValueScalar JOIN modelComposition ON propertyValueScalar.properties_name = modelComposition.properties_name) join materialsModels on allProp.materials_name = materialsModels.materials_name and  allProp.models_name = materialsModels.models_name where materialsModels.models_name = 'IsoElst' and materialsModels.materials_name = 'carbon';";
    model->setQuery(str, local_db);
    qDebug() << model->lastError();
    Properties->setModel(model);
    tabProperties->setWidget(Properties);

    setColumnWidth();
}

void API::createListOfGlobalTable(){

  //  qDebug()<<"connection is created";
    tables = new QListWidget();
    QStringList lst = global_db.tables();
    foreach (QString str, lst) {
        tables->addItem(str);
    }
    QDockWidget* wgt = new QDockWidget();
    wgt->setWidget(tables);
    wgt->setWindowTitle("List of tables");
    //m_Layout->addWidget(wgt, 2, 7, 1, 1);
    this->addDockWidget(Qt::BottomDockWidgetArea,wgt);
    connect(tables,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(TabAddToView(QListWidgetItem*)));
}

void API::TabAddToView(QListWidgetItem* p_item){
    QDockWidget* wgt = new QDockWidget();
    QTableView* view = new QTableView();
    //view->setEditTriggers(QTableView::NoEditTriggers);
    QSqlQueryModel* model = new QSqlQueryModel();
  //  QSqlQuery* query = new QSqlQuery();
    QString str ="SELECT * FROM " + p_item->text()+";";
//    qDebug()<<str;
    model->setQuery(str,global_db);
    view->setModel(model);
    wgt->setWidget(view);
    wgt->setWindowTitle(p_item->text());
    this->addDockWidget(Qt::LeftDockWidgetArea ,wgt);
}

void API::run_command(){
    QSqlQuery query ;

    if(this->command_form->rb_globalDb->isChecked()){
        query = global_db.exec(this->command_form->command_text->toPlainText());
    }
    else{
        query = local_db.exec(this->command_form->command_text->toPlainText());
    }
    if(query.isActive()){
        this->command_form->command_res->setText("The command is success");
        emit need_update_table_view();
    }
    else
        this->command_form->command_res->setText(query.lastError().text());

}

void API::update_table_view(){
    qDebug()<<"\nBegin update";
//    tables->clear();
//    QStringList lst = global_db.tables();
//    foreach (QString str, lst) {
//        tables->addItem(str);
//    }
    //QSqlQueryModel a  = ().setQuery("SELECT * FROM materialTypes;",local_db)

    if(l_Mat->model())
    dynamic_cast<QSqlQueryModel*>(l_Mat->model())->setQuery("SELECT name, description FROM materials;",local_db);

//    if(l_Model->model())
//    dynamic_cast<QSqlQueryModel*>(l_Model->model())->setQuery("SELECT * FROM materialsModels;",local_db);

//    if(l_Properties->model())
//    dynamic_cast<QSqlQueryModel*>(l_Properties->model())->setQuery("SELECT * FROM propertyValueScalar;",local_db);

//    if(Lib->model())
//    dynamic_cast<QSqlQueryModel*>(Lib->model())->setQuery("SELECT * FROM materialTypes;",global_db);
    QSqlQuery query(global_db);
    query.exec("SELECT * FROM materialTypes;");
    QStringList lst;
    lst << "Name" << "Description";
    Lib->setHeaderLabels(lst);
    Lib->clear();
    while(query.next())
    {
        QTreeWidgetItem *ptwgItem = new QTreeWidgetItem(Lib);
        ptwgItem->setText(0,query.value(0).toString());
        QTreeWidgetItem *ptwgItemDir = new QTreeWidgetItem(ptwgItem);
        ptwgItemDir->setText(1, query.value(1).toString());
    }
    tabLib->setWidget(Lib);
    setColumnWidth();
//    if(Mat->model())
//       dynamic_cast<QSqlQueryModel*>(Mat->model())->setQuery("SELECT * FROM materials;",global_db);

//    if(Model->model())
//        dynamic_cast<QSqlQueryModel*>(Model->model())->setQuery("SELECT * FROM materialsModels;",global_db);

//    if(Properties->model())
//    dynamic_cast<QSqlQueryModel*>(Properties->model())->setQuery("SELECT * FROM propertyValueScalar;",global_db);

    //qDebug()<<"\nend update";
}

void API::slotShowInsertForm()
{
    qDebug() << "InsertFormShow";
//     insert_form->setParent(this);
     insert_form->show();
     setEnabled(false);
     //this->addDockWidget(Qt::TopDockWidgetArea,insert_form->dck_indert_form);
     connect(insert_form, SIGNAL(closed()), this, SLOT(slotCloseInsertForm()));
}

void API::slotCloseInsertForm()
{
    insert_form->close();
    qDebug() << "closed";
    setEnabled(true);
}

void API::slotDeleteMat()
{
    QSqlQuery* localQuery;
    localQuery = new QSqlQuery(local_db);
    QString str;
    str= "DELETE FROM materials WHERE name = '" + nameMaterial + "';";
    localQuery->exec(str);
    qDebug() << localQuery->lastError();
    dynamic_cast<QSqlQueryModel*>(l_Mat->model())->setQuery("SELECT name, description FROM materials;",local_db);
    l_Model->setModel(nullptr);
    Properties->setModel(nullptr);

    setColumnWidth();
}

void API::slotDeleteModel()
{
    QSqlQuery* localQuery;
    localQuery = new QSqlQuery(local_db);
    QString str;
    QString nameModel =l_Model->model()->data(l_Model->model()->index(l_Model->currentIndex().row(), 0)).toString();
    str= "DELETE FROM materialsModels WHERE materials_name  = '" + nameMaterial + "' AND models_name = '" + nameModel + "';";
    localQuery->exec(str);
    qDebug() << localQuery->lastError();
    dynamic_cast<QSqlQueryModel*>(l_Model->model())->setQuery("SELECT models_name, description FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';",local_db);
    Properties->setModel(nullptr);

    setColumnWidth();
}

void API::slotSQLQuery(){
    if(flagSQLQuery)
    {
        command_form->dck_command_wdgt->setVisible(false);
    }
    else
    {
        command_form ->setContentsMargins(1,1,1,1);
        addDockWidget(Qt::BottomDockWidgetArea, command_form->dck_command_wdgt);
        command_form->dck_command_wdgt->setVisible(true);
    }
    flagSQLQuery = !flagSQLQuery;
    qDebug() << flagSQLQuery;
}

void API::setColumnWidth() {
    Mat->setColumnWidth(1, 220);
    Model->setColumnWidth(1,220);
    Properties->setColumnWidth(1,160);
    l_Model->setColumnWidth(1,220);
    l_Mat->setColumnWidth(1,220);
}

API::~API()
{

    insert_form->close();
    delete  insert_form;
    delete connectionForm;
    delete command_form;
    delete ui;
    delete m_Layout;

    delete Lib;
    delete Mat;
    delete Model;
    delete Properties;

    delete l_Mat;
    delete l_Model;

    delete tabLib;
    delete tabMat;
    delete tabModel;
    delete tabProperties;

    delete l_tabMat;
    delete l_tabModel;

    local_db.close();
    global_db.close();
    global_db.removeDatabase("qt_sql_default_connection");
    local_db.removeDatabase("qt_sql_default_connection");
    local_db.~QSqlDatabase();
    global_db.~QSqlDatabase();

}


