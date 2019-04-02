#include "api.h"
#include "ui_api.h"
#include <algorithm>
#include <QSize>

API::API(QWidget *parent) :
    QMainWindow(parent)
   // ui(new Ui::API)
{
    setWindowIcon(QIcon(":resources/sqldevops.png"));
    m_Layout = new QGridLayout;
    flagImport=false;
    flagSQLQuery = false;

    command_form = new cls_command_form(this, nullptr);

    Tree = new QTreeView();
    Tree->setAlternatingRowColors(true);
    Tree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(Tree,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_my_context_menu(const QPoint&)));

    Tree->show();
    QStringList headers;
    headers << tr("Title") << tr("Description");

    Lib = new QTreeWidget();
    Lib->setAlternatingRowColors(true);
    Lib->setStyleSheet("border: 1px solid lightgray;");
    QStringList lst;
    lst << "Name" << "Description";
    Lib->setHeaderLabels(lst);
    Mat = new QTableView();
    Mat->setAlternatingRowColors(true);
    Model = new QTableView();
    Properties = new QTableView();

    tabLib = new QDockWidget;
    tabLib->setMaximumWidth(250);
    tabLib->setWindowTitle("Классификация материалов");
    tabLib->setAllowedAreas(Qt::LeftDockWidgetArea);
    tabLib->setFeatures(QDockWidget::DockWidgetMovable);
    tabLib->setWidget(Tree);

    tabMat = new QDockWidget;
    tabMat->setWindowTitle("Материалы");
    tabMat->setAllowedAreas(Qt::LeftDockWidgetArea);
    tabMat->setFeatures(QDockWidget::DockWidgetMovable);

    tabModel = new QDockWidget;
    tabModel->setWindowTitle("Модели материала");
    tabModel->setAllowedAreas(Qt::LeftDockWidgetArea);
    tabModel->setFeatures(QDockWidget::DockWidgetMovable);

    tabProperties = new QDockWidget;
    tabProperties->setWindowTitle("Свойства материала");
    tabProperties->setAllowedAreas(Qt::LeftDockWidgetArea);
    tabProperties->setFeatures(QDockWidget::DockWidgetMovable);


    l_Mat = new QTableView();
    l_Model = new QTableView();

    l_tabMat = new QDockWidget;
    l_tabMat->setWindowTitle("Материалы");
    l_tabMat->setAllowedAreas(Qt::RightDockWidgetArea);
    l_tabMat->setFeatures(QDockWidget::DockWidgetMovable);

    l_tabModel = new QDockWidget;
    l_tabModel->setWindowTitle("Модели материала");
    l_tabModel->setAllowedAreas(Qt::RightDockWidgetArea);
    l_tabModel->setFeatures(QDockWidget::DockWidgetMovable);

    QWidget* body = new QWidget;
    body->setLayout(m_Layout);
    setCentralWidget(body);

    QWidget* glb_area = new QWidget();
    QGridLayout* glb_layout = new QGridLayout();
    QLabel* lbl_glb = new QLabel("Глобальная БД");
    QFont font = lbl_glb->font();
    font.setPixelSize(18);
    lbl_glb->setFont(font);
    glb_layout->addWidget(lbl_glb,0,1,Qt::AlignHCenter);
    glb_layout->setContentsMargins(0,0,0,0);
    glb_layout->addWidget(tabLib,1,0);
    glb_layout->addWidget(tabMat,1,1);
    glb_layout->addWidget(tabModel,1,2);
    glb_area->setLayout(glb_layout);

    QWidget* local_area = new QWidget();
    QLabel* lbl_loc = new QLabel("Локальная БД");
    lbl_loc->setFont(font);
    QGridLayout* local_layout = new QGridLayout();
    local_layout->setContentsMargins(0,0,0,0);
    local_layout->addWidget(lbl_loc,0,0,1,3,Qt::AlignHCenter);
    local_layout->addWidget(l_tabMat,1,0,1,1);
    local_layout->addWidget(l_tabModel,1,2,1,1);
    local_area->setLayout(local_layout);

    QSplitter* vSplit1 = new QSplitter(Qt::Vertical);
    vSplit1->addWidget(glb_area);
    vSplit1->addWidget(local_area);

    QWidget* prop = new QWidget();
    QVBoxLayout* lt = new QVBoxLayout();
    prop->setLayout(lt);
    QLabel* kostil = new QLabel("    ");
    kostil->setFont(font);
    lt->addWidget(kostil);
    lt->addWidget(tabProperties);
    lt->setContentsMargins(0,0,0,0);

    prop->setMaximumWidth(300);
    m_Layout->addWidget(vSplit1,0,0,1,1);
    m_Layout->addWidget(prop,0,1,1,1);

//    m_Layout->addWidget(tabMat,0,1,1,1);
//    m_Layout->addWidget(tabModel,0,2,1,1);
//    m_Layout->addWidget(tabProperties,0,3,2,1,Qt::AlignHCenter);
//    m_Layout->addWidget(l_tabMat,1,1,1,1);
//    m_Layout->addWidget(l_tabModel,1,2,1,1);

    QToolBar* ptb = new QToolBar("Панель инструментов");
    QMenu* pmnuConnect = new QMenu("&Подключение");
       QAction* pactConnect = new QAction ("Подключение к серверу...", nullptr) ;
       pactConnect -> setText ("&Подключение к серверу...");
       pactConnect -> setShortcut ( QKeySequence ("CTRL+O"));
       pactConnect->setIcon (QPixmap(":resources/addDB.png"));
       ptb->addAction(pactConnect);
       pmnuConnect->addAction(pactConnect);
       connect(pactConnect, SIGNAL(triggered(bool)) , this, SLOT(slotFormConnection()));
    menuBar()->addMenu(pmnuConnect);
    ptb->addSeparator();
    QMenu* pmnuTools = new QMenu("Инструменты");
       pactImport = new QAction ("Импорт", nullptr) ;
       pactImport -> setText ("&Импорт");
       pactImport -> setShortcut ( QKeySequence ("CTRL+I"));
       pactImport->setIcon (QPixmap(":resources/import.png"));
       pactImport->setEnabled(false);
       ptb->addAction(pactImport);
    pmnuTools->addAction(pactImport);
       pactExport = new QAction ("Экспорт", nullptr) ;
       pactExport -> setText ("&Экспорт");
       pactExport -> setShortcut ( QKeySequence ("CTRL+E"));
       pactExport->setIcon (QPixmap(":resources/export.png"));
       ptb->addAction(pactExport);
    pmnuTools->addAction(pactExport);

        pactAddData = new QAction ("Добавить данные", nullptr) ;
        pactAddData -> setText ("&Добавить данные");
        pactAddData -> setIcon (QIcon(":resources/addData.png"));
        ptb->addAction(pactAddData);
    pmnuTools->addAction(pactAddData);
        pactDeleteMat = new QAction ("Удалить материал", nullptr) ;
        pactDeleteMat -> setText ("&Удалить материал");
    pmnuTools->addAction(pactDeleteMat);
        pactDeleteModel = new QAction ("Удалить модель", nullptr) ;
        pactDeleteModel -> setText ("&Удалить модель");
    pmnuTools->addAction(pactDeleteModel);
        pactSQLQuery = new QAction ("Выполнить SQL запрос", nullptr) ;
        pactSQLQuery -> setText ("Выполнить SQL запрос");
        pactSQLQuery -> setIcon(QIcon(":resources/SQL.png"));
        ptb->addAction(pactSQLQuery);
    pmnuTools->addAction(pactSQLQuery);
    menuBar()->addMenu(pmnuTools);
    addToolBar(Qt::TopToolBarArea, ptb);
    QMenu* pmnuFAQ = new QMenu("Справка");
    pactFAQ = new QAction("О программе");
    pactFAQ->setIcon(QIcon(":resources/FAQ.png"));
    ptb->addSeparator();
    ptb->addAction(pactFAQ);
    pmnuFAQ->addAction(pactFAQ);
    menuBar()->addMenu(pmnuFAQ);

    local_db = QSqlDatabase::addDatabase("QSQLITE", "Local");
    global_db = QSqlDatabase::addDatabase("QPSQL");
    insert_form = new cls_insert_form();
    insert_form->global_db = &global_db;
    insert_form->local_db = &local_db;

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
    connect(pactFAQ, SIGNAL(triggered(bool)), this, SLOT(slotAbout()));
   // connect(this,SIGNAL(connection_is_created()),SLOT(createListOfGlobalTable()));
    connect(insert_form,SIGNAL(need_update_table_view()),this,SLOT(update_table_view()));

    statusBar()->showMessage("Подключите БД", 10000);
     local_db.open();
     QSqlQuery* localQuery;
     localQuery = new QSqlQuery(local_db);
     QString str = "PRAGMA foreign_keys = on";
     localQuery->exec(str);
     qDebug() << str;
     qDebug() << localQuery->lastError();
     str = "CREATE TABLE materials(id primary key, description text);";
     localQuery->exec(str);
     qDebug() << str;
     qDebug() << localQuery->lastError().text();
     str = "create table models(name text primary key, description text);";
     localQuery->exec(str);
     qDebug() << str;
     qDebug() << localQuery->lastError().text();
     str = "create table properties (name text primary key, description text);";
     localQuery->exec(str);
     qDebug() << str;
     qDebug() << localQuery->lastError().text();
     str = "create table modelComposition(models_name text references models(name) ON DELETE CASCADE, properties_name text  references properties(name));";
     localQuery->exec(str);
     qDebug() << str;
     qDebug() << localQuery->lastError().text();
     str = "CREATE TABLE materialsModels(materials_name text references materials(id) ON DELETE CASCADE, models_name text references models(name) ON DELETE CASCADE,  primary key(materials_name, models_name));";
     localQuery->exec(str);
     qDebug() << str;
     qDebug() << localQuery->lastError().text();
     str = "CREATE TABLE propertyValueScalar(materials_name text references materials(id) ON DELETE CASCADE, properties_name text, value float not null, primary key(materials_name, properties_name));";
     localQuery->exec(str);
     qDebug() << str;
     qDebug() << localQuery->lastError().text();
     QSqlQueryModel* model = new QSqlQueryModel();
     str ="SELECT id, description  FROM materials;";
     model->setQuery(str, local_db);
     l_Mat->setModel(model);
     l_tabMat->setWidget(l_Mat);
     connect(l_Mat, SIGNAL(clicked(QModelIndex)), this, SLOT(slotLocalSelectModel()));
}

void API::slot_my_context_menu(const QPoint& pos){
    QModelIndex index = Tree->indexAt(pos);
    if(index.isValid()){

        QString path = get_full_path(index);
        qDebug()<<"menu on  "<<path;
        QMenu* context_menu = new QMenu;
        int len = path.split('.').length();
        qDebug()<<"len="<<len;

        if(len == 1){
            QAction* pAct_add_branch = new QAction("Добавить классификацию");
            context_menu->addAction(pAct_add_branch);
            connect(pAct_add_branch,SIGNAL(triggered()),this,SLOT(slot_add_classification()));
        }

        if(len == 2){
            QAction* pAct_remove_classification = new QAction("Удалить классификацию");
            QAction* pAct_add_branch = new QAction("Добавить ветку");
            context_menu->addAction(pAct_add_branch);
            context_menu->addAction(pAct_remove_classification);
            connect(pAct_remove_classification,SIGNAL(triggered()),this, SLOT(slot_remove_classification()));
            connect(pAct_add_branch,SIGNAL(triggered()),this,SLOT(slot_add_branch()));
        }

        if(len>2){
            QAction* pAct_remove_branch = new QAction("Удалить ветку");
            QAction* pAct_add_branch = new QAction("Добавить ветку");
            context_menu->addAction(pAct_remove_branch);
            context_menu->addAction(pAct_add_branch);
            connect(pAct_remove_branch,SIGNAL(triggered()),this, SLOT(slot_remove_branch()));
            connect(pAct_add_branch,SIGNAL(triggered()),this,SLOT(slot_add_branch()));
        }

        if(!index.child(0,0).isValid() && len!=1){
            QAction* pAct_add_material = new QAction("Добавить материал");
            context_menu->addAction(pAct_add_material);
            connect(pAct_add_material,SIGNAL(triggered()),this,SLOT(slot_add_material()));
        }
        context_menu->popup(Tree->mapToGlobal(pos));
    }
}


void API::slot_remove_classification(){
    if(!Tree->currentIndex().isValid())
        return;
    QString path = get_full_path(Tree->currentIndex());
    qDebug()<<"remove classifications "<< path;
    QSqlQuery q(global_db);
    q.exec("DELETE FROM tree WHERE path <@ '" + path + "';");
    qDebug() << q.lastError();
    TreeModel* model = (TreeModel*)Tree->model();
    model->addData(path.split(QString(".")), model->getRootItem());
    QStringList headers;
    headers << tr("Title") << tr("Description");
    Tree->setModel(new TreeModel(headers, global_db));
    Tree->setColumnWidth(0, 250);
}

void API::slot_remove_branch(){
    if(!Tree->currentIndex().isValid())
        return;
    QString path = get_full_path(Tree->currentIndex());
    qDebug()<<"remove branch "<< path;
    QSqlQuery q(global_db);
    q.exec("DELETE FROM tree WHERE path <@ '" + path + "';");
    qDebug() << q.lastError();
    TreeModel* model = (TreeModel*)Tree->model();
    model->addData(path.split(QString(".")), model->getRootItem());
    QStringList headers;
    headers << tr("Title") << tr("Description");
    Tree->setModel(new TreeModel(headers, global_db));
    Tree->setColumnWidth(0, 250);
}

void API::slot_add_classification(){
    if(!Tree->currentIndex().isValid())
        return;
    qDebug()<<"classification "<<get_full_path(Tree->currentIndex());
    QInputDialog inputDialog;
    inputDialog.resize(400,140);
    inputDialog.setWindowTitle("Добавление классфикации");
    inputDialog.setLabelText("Введите название классификации");
    inputDialog.setTextValue("New classification");
    QFont font;
    font.setPixelSize(12);
    inputDialog.setFont(font);
    inputDialog.setTextEchoMode(QLineEdit::Normal);
    bool ok = !!inputDialog.exec();
    if(!ok)
        return;
    QString str = inputDialog.textValue();
    qDebug()<<str;
    QSqlQuery q(global_db);
    q.exec("INSERT INTO schemes(scheme) VALUES ('" + str + "');");
    q.exec("INSERT INTO tree(path) VALUES ('" + get_full_path(Tree->currentIndex()) + "." + str + "');");
    qDebug() << q.lastError();
    TreeModel* model = (TreeModel*)Tree->model();
    model->addData(str.split(QString(".")), model->getRootItem());
    QStringList headers;
    headers << tr("Title") << tr("Description");
    Tree->setModel(new TreeModel(headers, global_db));
}

void API::slot_add_branch(){
    if(!Tree->currentIndex().isValid())
        return;
     qDebug()<<"Branch  "<<get_full_path(Tree->currentIndex());
     QInputDialog inputDialog;
     inputDialog.resize(400,140);
     inputDialog.setWindowTitle("Добавление ветки");
     inputDialog.setLabelText("Введите название ветки");
     inputDialog.setTextValue("New branch");
     QFont font;
     font.setPixelSize(12);
     inputDialog.setFont(font);
     inputDialog.setTextEchoMode(QLineEdit::Normal);
     bool ok = !!inputDialog.exec();
     if(!ok)
         return;
     QString str = inputDialog.textValue();
     qDebug()<<str;
     QSqlQuery q(global_db);
     q.exec("INSERT INTO tree(path) VALUES ('" + get_full_path(Tree->currentIndex()) + "." + str + "');");
     qDebug() << q.lastError();
     TreeModel* model = (TreeModel*)Tree->model();
     model->addData(str.split(QString(".")), model->getRootItem());
     QStringList headers;
     headers << tr("Title") << tr("Description");
     Tree->setModel(new TreeModel(headers, global_db));
     Tree->setColumnWidth(0, 250);
}

void API::slot_add_material(){
    if(!Tree->currentIndex().isValid())
        return;
    qDebug()<<"Material  "<<get_full_path(Tree->currentIndex());

    QInputDialog inputDialog;
    inputDialog.resize(400,140);
    inputDialog.setWindowTitle("Добавление материала");
    inputDialog.setLabelText("Введите название материала");
    QFont font;
    font.setPixelSize(12);
    inputDialog.setFont(font);
    inputDialog.setTextValue("New material");
    inputDialog.setTextEchoMode(QLineEdit::Normal);
    bool ok = !!inputDialog.exec();
    if(!ok)
        return;
    QString str = inputDialog.textValue();
    qDebug()<<str;
    QString path = get_full_path(Tree->currentIndex());
    QSqlQuery q(global_db);
    q.exec("INSERT INTO materials(id) VALUES ('" + str + "');");
    qDebug() << q.lastError();
    q.exec("INSERT INTO material_branch(scheme, branch, id_material) VALUES ('" + getScheme(path) + "', '" + path + "', '" + str + "');");
    qDebug() << q.lastError();
}

QString API::get_full_path(const QModelIndex& index){
      QStringList res;
      QStringList lst = index.data().toStringList();
      for(auto a:lst){
        res+=a;
      }

      QModelIndex p_id = index;
      while(p_id.parent().isValid()){
          p_id = p_id.parent();
          lst = p_id.data().toStringList();
          for(auto a:lst){
                 res += a;
          }
      }

      QString path;
      for(int i = res.length()-1; i!=0; i--){
            path += res[i] + ".";
      }

      path += res[0];
      return path;
}

QString API::getScheme(const QString& path){
      QString scheme;
      QStringList l = path.split(QString("."));
      if(l.count() > 1)
        scheme = l[1];
      return scheme;
}

void API::slotFormConnection()
{
    connectionForm = new cls_connectionForm();
    connectionForm->setWindowIcon(QIcon(":resources/addDB.png"));
    connect(connectionForm->pbtnConnect,SIGNAL(clicked()), this, SLOT(slotConnection()));
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

    QSqlQuery* query = new QSqlQuery(global_db);
    query->exec("SELECT * FROM materialTypes;");
    QStringList lst;
    Lib->clear();
    while(query->next())
    {
        QTreeWidgetItem *ptwgItem = new QTreeWidgetItem(Lib);
        ptwgItem->setText(0,query->value(0).toString());
        QTreeWidgetItem *ptwgItemDir = new QTreeWidgetItem(ptwgItem);
        ptwgItemDir->setText(1, query->value(1).toString());
    }
    tabMat->show();
    tabModel->show();
    tabProperties->show();
    l_tabMat->show();
    l_tabModel->show();
    connect(Tree, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSelectMat()));
    this->insert_form->global_db=&global_db;
    this->insert_form->local_db=&local_db;
    setColumnWidth();
    pactSQLQuery->setEnabled(true);
    statusBar()->showMessage("Готово", 3000);

    QStringList headers;
    headers << tr("Title") << tr("Description");
    TreeModel *Tree_Model = new TreeModel(headers, global_db);
    Tree->setModel(Tree_Model);
    Tree->setColumnWidth(0, 250);
    qDebug() << Tree_Model->getRootItem()->data(0);
    Tree->header()->hide();
    return true;
}

void API::slotSelectMat()
{
    QString path = get_full_path(Tree->currentIndex());
    qDebug() << path;
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, description FROM material_branch RIGHT JOIN materials ON material_branch.id_material = materials.id WHERE material_branch.branch  <@ '" + path + "';");
    qDebug() << model->lastError();
    Mat->setModel(model);
    Model->setModel(nullptr);
    Properties->setModel(nullptr);
    Mat->setAlternatingRowColors(true);
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
        Properties->setModel(nullptr);
        Model->setAlternatingRowColors(true);
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
    Properties->setAlternatingRowColors(true);
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
    QSqlQuery q(local_db);
    qDebug() << "TESTING" << q.lastError();
    qDebug() << nameMaterial;
    globalQuery->exec("SELECT * FROM materials WHERE id ='"+ nameMaterial +"';");

    while(globalQuery->next())
    {
        str = "INSERT INTO materials(id, description) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(2).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }
    globalQuery->exec("SELECT * FROM models;");
    while(globalQuery->next())
    {
        str = "INSERT INTO models(name, description) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }


    globalQuery->exec("SELECT * FROM properties;");
    while(globalQuery->next())
    {
        str = "INSERT INTO properties(name) values ('" + globalQuery->value(0).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }

    globalQuery->exec("SELECT * FROM modelComposition;");
    while(globalQuery->next())
    {
        str = "INSERT INTO modelComposition(models_name, properties_name) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }

    globalQuery->exec("SELECT * FROM materialsModels WHERE models_name = '" + nameModel + "' AND materials_name = '" + nameMaterial + "';");
    while(globalQuery->next())
    {
        str = "INSERT INTO materialsModels(materials_name, models_name) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }
    str ="SELECT * FROM materialTypes;";

    globalQuery->exec("SELECT * FROM propertyValueScalar WHERE materials_name = '" + nameMaterial + "';");
    while(globalQuery->next())
    {
        str = "INSERT INTO propertyValueScalar(materials_name, properties_name, value) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "', '" + globalQuery->value(2).toString() + "');";
        localQuery->exec(str);
        qDebug() << str;
        qDebug() << localQuery->lastError();
    }
    QSqlQueryModel* model = new QSqlQueryModel();
    str ="SELECT id, description  FROM materials;";
    model->setQuery(str, local_db);
    l_Mat->setModel(model);
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
   QString str = "INSERT INTO material_branch(name) VALUES ('" + newLib +"');";
   globalQuery->exec(str);
   qDebug() << globalQuery->lastError();
   QSqlQueryModel* model = new QSqlQueryModel();
   QSqlQuery* localQuery = new QSqlQuery(local_db);
   localQuery->exec("SELECT * FROM materials;");
   while(localQuery->next())
   {
       qDebug() << localQuery->value(0).toString();
       str = "INSERT INTO materials(id, description ) VALUES ('" + localQuery->value(0).toString() + "', '"+ localQuery->value(2).toString() +"');";
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
   tabLib->setWidget(Tree);

    setColumnWidth();
    statusBar()->showMessage("Успешно", 3000);
}

void API::slotLocalSelectModel()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    nameMaterial = l_Mat->model()->data(l_Mat->model()->index(l_Mat->currentIndex().row(), 0)).toString();
    QString str = "SELECT models_name, description "
                  "FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';";
    model->setQuery(str, local_db);
    qDebug() << model->lastError();
    l_Model->setModel(model);
    Properties->setModel(nullptr);
    l_Model->setAlternatingRowColors(true);
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
    Properties->setAlternatingRowColors(true);
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
    tabLib->setWidget(Tree);
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

void API::slotAbout()
{
    QMessageBox::about(this, "О программе", "Шамшидов О.\nЧепурной С. \nФН11-32");
}

API::~API()
{

    insert_form->close();
    qDebug()<<"destuctor";
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


