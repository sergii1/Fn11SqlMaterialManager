#include "api.h"
#include "ui_api.h"
#include <algorithm>
#include <QSize>
#include <QTimer>
#include <QTime>
API::API(const QString& pathToDB, QWidget *parent) :
    QMainWindow(parent)
   // ui(new Ui::API)
{
    setWindowIcon(QIcon(":resources/sqldevops.png"));
    m_Layout = new QGridLayout;
    flagImport=false;
    flagSQLQuery = false;


    Tree = new QTreeView();
    Tree->setCornerWidget(new QLabel("corner"));
    Tree->setAlternatingRowColors(true);
    Tree->setContextMenuPolicy(Qt::CustomContextMenu);
    Tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(Tree,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_TreeContextMenu(const QPoint&)));

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
    Mat->setContextMenuPolicy(Qt::CustomContextMenu);
    Mat->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(Mat,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_MatContextMenu(const QPoint&)));

    Model = new QTableView();
    Model->setAlternatingRowColors(true);
    Model->setContextMenuPolicy(Qt::CustomContextMenu);
    Model->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(Model,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_ModelContextMenu(const QPoint&)));

    Properties = new QTableView();
    Properties->setAlternatingRowColors(true);
    Properties->setContextMenuPolicy(Qt::CustomContextMenu);
    Properties->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(Properties,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_PropertiesContextMenu(const QPoint&)));

    localMat = new QTableView();
    localMat->setAlternatingRowColors(true);
    localMat->setContextMenuPolicy(Qt::CustomContextMenu);
    localMat->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(localMat,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_Local_MatContextMenu(const QPoint&)));

    localModel = new QTableView();
    localModel->setAlternatingRowColors(true);
    localModel->setContextMenuPolicy(Qt::CustomContextMenu);
    localModel->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(localModel,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_Local_ModelContextMenu(const QPoint&)));

    tabLib = new QDockWidget;
    tabLib->setMaximumWidth(320);
    QFont*font1 = new QFont();
    font1->setPointSize(9);
    //tabLib->setWindowTitle("Классификация материалов")
    tabLib->setTitleBarWidget(new QLabel("Классифиикация материалов"));
    ((QLabel*)tabLib->titleBarWidget())->setFont(*font1);
    ((QLabel*)tabLib->titleBarWidget())->setAlignment(Qt::AlignCenter);
    tabLib->titleBarWidget()->setStyleSheet("QLabel {background: #80daeb}");
    tabLib->setWidget(Tree);

    tabMat = new QDockWidget;
    tabMat->setTitleBarWidget(new QLabel("Материалы"));
    ((QLabel*)tabMat->titleBarWidget())->setAlignment(Qt::AlignCenter);
    tabMat->titleBarWidget()->setStyleSheet("background: #80daeb");
    tabMat->titleBarWidget()->setFont(*font1);

    tabModel = new QDockWidget;
    tabModel->setTitleBarWidget(new QLabel("Модели материала"));
    ((QLabel*)tabModel->titleBarWidget())->setAlignment(Qt::AlignCenter);
    tabModel->titleBarWidget()->setStyleSheet("background: #80daeb");
    tabModel->titleBarWidget()->setFont(*font1);

    tabProperties = new QDockWidget;
    tabProperties->setTitleBarWidget(new QLabel("Свойства материала"));
    ((QLabel*)tabProperties->titleBarWidget())->setAlignment(Qt::AlignCenter);
    tabProperties->titleBarWidget()->setStyleSheet("background: #FFFFFF");
    tabProperties->titleBarWidget()->setFont(*font1);

    localTabMat = new QDockWidget;
    localTabMat->setTitleBarWidget(new QLabel("Материалы"));
    ((QLabel*)localTabMat->titleBarWidget())->setAlignment(Qt::AlignCenter);
    localTabMat->titleBarWidget()->setStyleSheet("background: #3eb489");
    localTabMat->titleBarWidget()->setFont(*font1);

    localTabModel = new QDockWidget;
    localTabModel->setTitleBarWidget(new QLabel("Модели материала"));
    ((QLabel*)localTabModel->titleBarWidget())->setAlignment(Qt::AlignCenter);
    localTabModel->titleBarWidget()->setStyleSheet("background: #3eb489");
    localTabModel->titleBarWidget()->setFont(*font1);

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
    tabLib->setStyleSheet("border: blue");
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
    local_layout->addWidget(localTabMat,1,0,1,1);
    local_layout->addWidget(localTabModel,1,2,1,1);
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
       connect(pactConnect, SIGNAL(triggered(bool)) , this, SLOT(slot_FormConnection()));
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

    menuBar()->addMenu(pmnuTools);
    addToolBar(Qt::TopToolBarArea, ptb);
    QMenu* pmnuFAQ = new QMenu("Справка");
    pactFAQ = new QAction("О программе");
    pactFAQ->setIcon(QIcon(":resources/FAQ.png"));
    ptb->addSeparator();
    ptb->addAction(pactFAQ);
    pmnuFAQ->addAction(pactFAQ);
    menuBar()->addMenu(pmnuFAQ);

    localDB = QSqlDatabase::addDatabase("QSQLITE", "Local");
    globalDB = QSqlDatabase::addDatabase("QPSQL");
    insertForm = new cls_insert_form();
    insertForm->globalDB = &globalDB;
    insertForm->localDB = &localDB;

    Mat->verticalHeader()->setDefaultSectionSize(28);
    Model->verticalHeader()->setDefaultSectionSize(28);
    Properties->verticalHeader()->setDefaultSectionSize(28);
    localMat->verticalHeader()->setDefaultSectionSize(28);
    localModel->verticalHeader()->setDefaultSectionSize(28);
    connect(this,SIGNAL(needUpdateTableView()),this,SLOT(slot_UpdateTableView()));
    connect(pactImport, SIGNAL(triggered(bool)), this, SLOT(slot_Import()));
    connect(pactExport, SIGNAL(triggered(bool)), this, SLOT(slot_Export()));
    connect(pactAddData, SIGNAL(triggered(bool)), this, SLOT(slot_ShowInsertForm()));
    connect(pactDeleteMat, SIGNAL(triggered(bool)), this, SLOT(slot_DeleteMat()));
    connect(pactDeleteModel, SIGNAL(triggered(bool)), this, SLOT(slot_DeleteModel()));
    connect(pactFAQ, SIGNAL(triggered(bool)), this, SLOT(slot_About()));
    connect(insertForm,SIGNAL(needUpdateTableView()),this,SLOT(slot_UpdateTableView()));

    statusBar()->showMessage("Подключите БД", 10000);
    localDB.setDatabaseName(pathToDB);
    localDB.open();

     QSqlQuery* localQuery;
     localQuery = new QSqlQuery(localDB);
     QString str = "PRAGMA foreign_keys = on";
     if(!localQuery->exec(str)){
        qDebug() << localQuery->lastQuery();
        qDebug() << localQuery->lastError().text();
     }

     str = "CREATE TABLE materials(id primary key, description text);";
     if(!localQuery->exec(str)){
        qDebug() << localQuery->lastQuery();
        qDebug() << localQuery->lastError().text();
     }

     str = "create table models(name text primary key, description text);";
     if(!localQuery->exec(str)){
        qDebug() << localQuery->lastQuery();
        qDebug() << localQuery->lastError().text();
     }

     str = "create table properties (name text primary key, description text);";
     if(!localQuery->exec(str)){
        qDebug() << localQuery->lastQuery();
        qDebug() << localQuery->lastError().text();
     }

     str = "create table modelComposition(models_name text references models(name) ON DELETE CASCADE, properties_name text  references properties(name));";
     if(!localQuery->exec(str)){
        qDebug() << localQuery->lastQuery();
        qDebug() << localQuery->lastError().text();
     }

     str = "CREATE TABLE materialsModels(materials_name text references materials(id) ON DELETE CASCADE, models_name text references models(name) ON DELETE CASCADE,  primary key(materials_name, models_name));";
     if(!localQuery->exec(str)){
        qDebug() << localQuery->lastQuery();
        qDebug() << localQuery->lastError().text();
     }

     str = "CREATE TABLE propertyValueScalar(materials_name text references materials(id) ON DELETE CASCADE, properties_name text, value float not null, primary key(materials_name, properties_name));";
     if(!localQuery->exec(str)){
        qDebug() << localQuery->lastQuery();
        qDebug() << localQuery->lastError().text();
     }

     QSqlQueryModel* model = new QSqlQueryModel();
     str ="SELECT id, description  FROM materials;";
     model->setQuery(str, localDB);
     localMat->setModel(model);
     localTabMat->setWidget(localMat);
     connect(localMat, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_LocalSelectModel()));

     connectionForm = new cls_connectionForm();
     createConnection();
}

void API::slot_TreeContextMenu(const QPoint& pos){
    QModelIndex index = Tree->indexAt(pos);
    if(index.isValid()){
        QString path = getFullPath(index);
        qDebug()<<"menu on  "<<path;
        QMenu* context_menu = new QMenu;
        int len = path.split('.').length();
        qDebug()<<"len="<<len;

        if(len == 1){
            QAction* pAct_add_branch = new QAction("Добавить классификацию");
            context_menu->addAction(pAct_add_branch);
            connect(pAct_add_branch,SIGNAL(triggered()),this,SLOT(slot_AddClassification()));
         }

        if(len == 2){

            QAction* pAct_remove_classification = new QAction("Удалить классификацию");
            QAction* pAct_add_branch = new QAction("Добавить ветку");
            context_menu->addAction(pAct_add_branch);
            context_menu->addAction(pAct_remove_classification);
            connect(pAct_remove_classification,SIGNAL(triggered()),this, SLOT(slot_RemoveClassification()));
            connect(pAct_add_branch,SIGNAL(triggered()),this,SLOT(slot_AddBranch()));
        }

        if(len>2){
            QAction* pAct_remove_branch = new QAction("Удалить ветку");
            QAction* pAct_add_branch = new QAction("Добавить ветку");
            context_menu->addAction(pAct_remove_branch);
            context_menu->addAction(pAct_add_branch);
            connect(pAct_remove_branch,SIGNAL(triggered()),this, SLOT(slot_RemoveBranch()));
            connect(pAct_add_branch,SIGNAL(triggered()),this,SLOT(slot_AddBranch()));
        }

        if(!index.child(0,0).isValid() && len!=1){
            QAction* pAct_add_material = new QAction("Добавить материал");
            context_menu->addAction(pAct_add_material);
            connect(pAct_add_material,SIGNAL(triggered()),this,SLOT(slot_AddMaterial()));
        }
        context_menu->popup(Tree->mapToGlobal(pos));
    }
}

void API::slot_MatContextMenu(const QPoint& pos){
    QModelIndex index = Mat->currentIndex();
    QStringList lst =  index.data().toStringList();
    for(QString& str:lst){
        qDebug()<<str;
    }
    QMenu* context_menu = new QMenu;
    QAction* pAct_AddMat = new QAction("Добавить материал");
    context_menu->addAction(pAct_AddMat);
    connect(pAct_AddMat,SIGNAL(triggered()),this, SLOT(slot_add_material()));
    context_menu->popup(Mat->mapToGlobal(pos));
}

void API::slot_ModelContextMenu(const QPoint& pos){
    QModelIndex index = Model->currentIndex();
    QStringList lst =  index.data().toStringList();
    for(QString& str:lst){
        qDebug()<<str;
    }
    QMenu* context_menu = new QMenu;
    QAction* pAct_AddModel = new QAction("Добавить Модель");
    context_menu->addAction(pAct_AddModel);
    connect(pAct_AddModel,SIGNAL(triggered()),this, SLOT(slot_add_model()));
    context_menu->popup(Model->mapToGlobal(pos));

}

void API::slot_PropertiesContextMenu(const QPoint& pos){
    QModelIndex index = Properties->currentIndex();
    QStringList lst =  index.data().toStringList();
    for(QString& str:lst){
        qDebug()<<str;
    }
    QMenu* context_menu = new QMenu;
    QAction* pAct_AddProp = new QAction("Добавить свойство");
    context_menu->addAction(pAct_AddProp);
    connect(pAct_AddProp,SIGNAL(triggered()),this, SLOT(slot_add_properties()));
    context_menu->popup(Properties->mapToGlobal(pos));
}

void API::slot_Local_MatContextMenu(const QPoint& pos){
    qDebug()<<"local mat context menu";
    QModelIndex index = localMat->indexAt(pos);
    QStringList lst =  index.data().toStringList();
    for(QString& str:lst){
        qDebug()<<str;
    }
    QMenu* context_menu = new QMenu();
    QAction* pAct_LocalAddMat = new QAction("Добавить материал");
    context_menu->addAction(pAct_LocalAddMat);
    connect(pAct_LocalAddMat,SIGNAL(triggered()),this, SLOT(slot_local_add_mat()));
    context_menu->popup(localMat->mapToGlobal(pos));
}

void API::slot_Local_ModelContextMenu(const QPoint& pos){
    QModelIndex index = localModel->currentIndex();
    QStringList lst =  index.data().toStringList();
    for(QString& str:lst){
        qDebug()<<str;
    }
    QMenu* context_menu = new QMenu;
    QAction* pAct_LocalAddModel = new QAction("Добавить модель");
    context_menu->addAction(pAct_LocalAddModel);
    connect(pAct_LocalAddModel,SIGNAL(triggered()),this, SLOT(slot_local_add_model()));
    context_menu->popup(localModel->mapToGlobal(pos));
}

void API::slot_local_add_model(){}

void API::slot_local_add_mat(){}

void API::slot_add_properties(){}

void API::slot_add_model(){}

void API::slot_add_material(){}

void API::slot_RemoveClassification(){
    if(!Tree->currentIndex().isValid())
        return;
    QString path = getFullPath(Tree->currentIndex());
    qDebug()<<"remove classifications "<< path;
    QSqlQuery q(globalDB);
    q.exec("DELETE FROM tree WHERE path <@ '" + path + "';");
    qDebug() << q.lastError();
    TreeModel* model = (TreeModel*)Tree->model();
    model->addData(path.split(QString(".")), model->getRootItem());
    QStringList headers;
    headers << tr("Title") << tr("Description");
    Tree->setModel(new TreeModel(headers, globalDB));
    Tree->setColumnWidth(0, 250);
}

void API::slot_RemoveBranch(){
    if(!Tree->currentIndex().isValid())
        return;
    QString path = getFullPath(Tree->currentIndex());
    //qDebug()<<"remove branch "<< path;
    QSqlQuery q(globalDB);
    q.exec("DELETE FROM tree WHERE path <@ '" + path + "';");
    qDebug() << q.lastError();
    TreeModel* model = (TreeModel*)Tree->model();
    model->addData(path.split(QString(".")), model->getRootItem());
    QStringList headers;
    headers << tr("Title") << tr("Description");
    Tree->setModel(new TreeModel(headers, globalDB));
    Tree->setColumnWidth(0, 250);
}

void API::slot_AddClassification(){
    if(!Tree->currentIndex().isValid())
        return;
    QString path = getFullPath(Tree->currentIndex());
   // qDebug()<<"classification "<<path;
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
    QSqlQuery q(globalDB);
    q.exec("INSERT INTO schemes(scheme) VALUES ('" + str + "');");
    q.exec("INSERT INTO tree(path) VALUES ('" + path + "." + str + "');");
    qDebug() << q.lastError();
    TreeModel* model = (TreeModel*)Tree->model();
    model->addData(str.split(QString(".")), model->getRootItem());
    QStringList headers;
    headers << tr("Title") << tr("Description");
    Tree->setModel(new TreeModel(headers, globalDB));
}

void API::slot_AddBranch(){
    if(!Tree->currentIndex().isValid())
        return;
    QString path = getFullPath(Tree->currentIndex());
    //qDebug()<<"Branch  "<<getFullPath(Tree->currentIndex());
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
    QSqlQuery q(globalDB);
    q.exec("INSERT INTO tree(path) VALUES ('" + path + "." + str + "');");
    qDebug() << q.lastError();
    TreeModel* model = (TreeModel*)Tree->model();
    model->addData(str.split(QString(".")), model->getRootItem());
    QStringList headers;
    headers << tr("Title") << tr("Description");
    Tree->setModel(new TreeModel(headers, globalDB));
    Tree->setColumnWidth(0, 250);
}

void API::slot_AddMaterial(){
    if(!Tree->currentIndex().isValid())
        return;
    qDebug()<<"Material  "<<getFullPath(Tree->currentIndex());

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
    QString path = getFullPath(Tree->currentIndex());
    QSqlQuery q(globalDB);
    q.exec("INSERT INTO materials(id) VALUES ('" + str + "');");
    qDebug() << q.lastError();
    q.exec("INSERT INTO material_branch(scheme, branch, id_material) VALUES ('" + getScheme(path) + "', '" + path + "', '" + str + "');");
    qDebug() << q.lastError();
}

QString API::getFullPath(const QModelIndex& index){
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

void API::slot_FormConnection()
{
    connectionForm->setWindowIcon(QIcon(":resources/addDB.png"));
    connect(connectionForm->pbtnConnect,SIGNAL(clicked()), this, SLOT(slot_Connection()));
    connectionForm->show();
}

void API::slot_Connection()
{
    if(createConnection()){
        connectionForm->close();
        emit connectionIsCreated();
    }

}

bool API::createConnection()
{
    globalDB.setDatabaseName(connectionForm->nameDB->text());
    globalDB.setUserName(connectionForm->nameUser->text());
    globalDB.setHostName(connectionForm->Host->text());
    globalDB.setPort(connectionForm->Port->text().toInt());
    globalDB.setPassword(connectionForm->Password->text());
    if (!globalDB.open()) {
        qDebug()<<"db not open";
        QMessageBox* pmbx =
         new QMessageBox(QMessageBox::Warning,
         "Warning",
         "Ошибка открытия БД, попробуйте снова\n\n" + globalDB.lastError().text());
        pmbx->show();
        statusBar()->showMessage("Ошибка открытия БД", 3000);
        statusBar()->showMessage("Ошибка подключения", 3000);
     }

    QSqlQuery* query = new QSqlQuery(globalDB);
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
    localTabMat->show();
    localTabModel->show();
    connect(Tree, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_SelectMat()));
    this->insertForm->globalDB=&globalDB;
    this->insertForm->localDB=&localDB;
    setColumnWidth();
    statusBar()->showMessage("Готово", 3000);

    QStringList headers;
    headers << tr("Title") << tr("Description");
    TreeModel *Tree_Model = new TreeModel(headers, globalDB);
    Tree->setModel(Tree_Model);
    Tree->setColumnWidth(0, 500);
    qDebug() << Tree_Model->getRootItem()->data(0);
    Tree->header()->hide();
    return true;
}

void API::slot_SelectMat()
{
    QString path = getFullPath(Tree->currentIndex());
    qDebug() << path;
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, description FROM material_branch RIGHT JOIN materials ON material_branch.id_material = materials.id WHERE material_branch.branch  <@ '" + path + "';");
    qDebug() << model->lastError();
    Mat->setModel(model);
    Model->setModel(nullptr);
    Properties->setModel(nullptr);
    Mat->setAlternatingRowColors(true);
    tabMat->setWidget(Mat);
    connect(Mat, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_SelectModel()));
    setColumnWidth();
    pactImport->setEnabled(false);
}

QString nameMaterial;

void API::slot_SelectModel()
{
    //view->setEditTriggers(QTableView::NoEditTriggers);
        QSqlQueryModel* model = new QSqlQueryModel();
        nameMaterial = Mat->model()->data(Mat->model()->index(Mat->currentIndex().row(), 0)).toString();
        QTime time;
        qDebug() << time.currentTime().toString();
        QString str = "SELECT models_name, description FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';";
        globalDB.open();

        model->setQuery(str, globalDB);
        qDebug() << time.currentTime().toString();
        Model->setModel(model);
        Properties->setModel(nullptr);
        Model->setAlternatingRowColors(true);
        tabModel->setWidget(Model);
        connect(Model, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_SelectProperties()));
        setColumnWidth();
        pactImport->setEnabled(false);
}

void API::slot_SelectProperties()
{
    QString nameModel =Model->model()->data(Model->model()->index(Model->currentIndex().row(), 0)).toString();
    QSqlQueryModel* model = new QSqlQueryModel();
    QString str = "select  DISTINCT properties_name as property, value from  (select materials_name, models_name , propertyValueScalar.properties_name, value from  propertyValueScalar join modelComposition  on propertyValueScalar.properties_name = modelComposition.properties_name )  as allProp  join materialsModels on  allProp.materials_name = materialsModels.materials_name and allProp.models_name = materialsModels.models_name where materialsModels.models_name = '" + nameModel + "' and materialsModels.materials_name = '" + nameMaterial +"';";
    //QString str = "SELECT properties_name, value FROM (SELECT materials_name, models_name , properties_name, value, models_name FROM propertyValueScalar JOIN modelComposition ON propertyValueScalar.properties_name = modelComposition.properties_name) join materialsModels on allProp.materials_name = materialsModels.materials_name and  allProp.models_name = materialsModels.models_name where materialsModels.models_name = 'IsoElst' and materialsModels.materials_name = 'carbon';";
    model->setQuery(str, globalDB);
    Properties->setModel(model);
    Properties->setAlternatingRowColors(true);
    tabProperties->setWidget(Properties);
    tabProperties->titleBarWidget()->setStyleSheet("background: #80daeb");
    pactImport->setEnabled(true);
    setColumnWidth();

}

void API::slot_Import()
{
    globalDB.close();
       QSqlQuery* localQuery;
//    QString str = "CREATE TABLE materialTypes(name text primary key, description text);";
//    localQuery->exec(str);
    QSqlQuery* globalQuery;
    if (globalDB.open())
        globalQuery = new QSqlQuery(globalDB);
    else return;
    localQuery = new QSqlQuery(localDB);
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
    QSqlQuery q(localDB);
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
    model->setQuery(str, localDB);
    localMat->setModel(model);
    flagImport = true;
    setColumnWidth();
    statusBar()->showMessage("Успешно", 3000);
}

void API::slot_Export()
{
    QSqlQuery* globalQuery = new QSqlQuery(globalDB);
    QSqlQuery* localQuery = new QSqlQuery(localDB);
    localQuery->exec("SELECT * FROM materials;");
    QString str;
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
    QString path = getFullPath(Tree->currentIndex());
    localQuery->exec("SELECT * FROM materials;");
    while(localQuery->next())
    {
        //qDebug() << localQuery->value(0).toString();
        str = "INSERT INTO material_branch(scheme, branch, id_material) VALUES ('" + getScheme(path) + "', '" + path + "', '" + localQuery->value(0).toString() + "');";
        globalQuery->exec(str);
    }
        globalQuery->exec(str);
    qDebug() << str;
    qDebug() << globalQuery->lastError();
}

void API::slot_AddLib(const QString & newLib)
{
   exportForm->close();
   QSqlQuery* globalQuery;
   if(globalDB.open())
        globalQuery = new QSqlQuery(globalDB);
   //newLib = InputLib->toPlainText();
   QString str = "INSERT INTO material_branch(name) VALUES ('" + newLib +"');";
   globalQuery->exec(str);
   qDebug() << globalQuery->lastError();
   QSqlQueryModel* model = new QSqlQueryModel();
   QSqlQuery* localQuery = new QSqlQuery(localDB);

   QSqlQuery* query = new QSqlQuery(globalDB);
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

void API::slot_LocalSelectModel()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    nameMaterial = localMat->model()->data(localMat->model()->index(localMat->currentIndex().row(), 0)).toString();
    QString str = "SELECT models_name, description "
                  "FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';";
    model->setQuery(str, localDB);
    qDebug() << model->lastError();
    localModel->setModel(model);
    Properties->setModel(nullptr);
    localModel->setAlternatingRowColors(true);
    localTabModel->setWidget(localModel);
    connect(localModel, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_LocalSelectProperties()));

    setColumnWidth();
}

void API::slot_LocalSelectProperties()
{
    QString nameModel =localModel->model()->data(localModel->model()->index(localModel->currentIndex().row(), 0)).toString();
    QSqlQueryModel* model = new QSqlQueryModel();
    QString str = "select DISTINCT properties_name as property, value from  (select materials_name, models_name , propertyValueScalar.properties_name, value from  propertyValueScalar join modelComposition  on propertyValueScalar.properties_name = modelComposition.properties_name )  as allProp  join materialsModels on  allProp.materials_name = materialsModels.materials_name and allProp.models_name = materialsModels.models_name where materialsModels.models_name = '" + nameModel + "' and materialsModels.materials_name = '" + nameMaterial +"';";
    //QString str = "SELECT properties_name, value FROM (SELECT materials_name, models_name , properties_name, value, models_name FROM propertyValueScalar JOIN modelComposition ON propertyValueScalar.properties_name = modelComposition.properties_name) join materialsModels on allProp.materials_name = materialsModels.materials_name and  allProp.models_name = materialsModels.models_name where materialsModels.models_name = 'IsoElst' and materialsModels.materials_name = 'carbon';";
    model->setQuery(str, localDB);
    qDebug() << model->lastError();
    Properties->setModel(model);
    Properties->setAlternatingRowColors(true);
    tabProperties->setWidget(Properties);
    tabProperties->titleBarWidget()->setStyleSheet("background: #3eb489");
    setColumnWidth();
}



void API::slot_UpdateTableView(){
    qDebug()<<"\nBegin update";
//    tables->clear();
//    QStringList lst = global_db.tables();
//    foreach (QString str, lst) {
//        tables->addItem(str);
//    }
    //QSqlQueryModel a  = ().setQuery("SELECT * FROM materialTypes;",local_db)

    if(localMat->model())
    dynamic_cast<QSqlQueryModel*>(localMat->model())->setQuery("SELECT id, description FROM materials;",localDB);

//    if(l_Model->model())
//    dynamic_cast<QSqlQueryModel*>(l_Model->model())->setQuery("SELECT * FROM materialsModels;",local_db);

//    if(l_Properties->model())
//    dynamic_cast<QSqlQueryModel*>(l_Properties->model())->setQuery("SELECT * FROM propertyValueScalar;",local_db);

//    if(Lib->model())
//    dynamic_cast<QSqlQueryModel*>(Lib->model())->setQuery("SELECT * FROM materialTypes;",global_db);
    QSqlQuery query(globalDB);
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

void API::slot_ShowInsertForm()
{
    qDebug() << "InsertFormShow";
//     insert_form->setParent(this);
     insertForm->show();
     setEnabled(false);
     //this->addDockWidget(Qt::TopDockWidgetArea,insert_form->dck_indert_form);
     connect(insertForm, SIGNAL(closed()), this, SLOT(slot_CloseInsertForm()));
}

void API::slot_CloseInsertForm()
{
    insertForm->close();
    qDebug() << "closed";
    setEnabled(true);
}

void API::slot_DeleteMat()
{
    QSqlQuery* localQuery;
    localQuery = new QSqlQuery(localDB);
    QString str;
    str= "DELETE FROM materials WHERE name = '" + nameMaterial + "';";
    localQuery->exec(str);
    qDebug() << localQuery->lastError();
    dynamic_cast<QSqlQueryModel*>(localMat->model())->setQuery("SELECT name, description FROM materials;",localDB);
    localModel->setModel(nullptr);
    Properties->setModel(nullptr);

    setColumnWidth();
}

void API::slot_DeleteModel()
{
    QSqlQuery* localQuery;
    localQuery = new QSqlQuery(localDB);
    QString str;
    QString nameModel =localModel->model()->data(localModel->model()->index(localModel->currentIndex().row(), 0)).toString();
    str= "DELETE FROM materialsModels WHERE materials_name  = '" + nameMaterial + "' AND models_name = '" + nameModel + "';";
    localQuery->exec(str);
    qDebug() << localQuery->lastError();
    dynamic_cast<QSqlQueryModel*>(localModel->model())->setQuery("SELECT models_name, description FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';",localDB);
    Properties->setModel(nullptr);

    setColumnWidth();
}


void API::setColumnWidth() {
    Mat->setColumnWidth(1, 220);
    Model->setColumnWidth(1,220);
    Properties->setColumnWidth(1,160);
    localModel->setColumnWidth(1,220);
    localMat->setColumnWidth(1,220);
}

void API::slot_About()
{
    QMessageBox::about(this, "О программе", "Шамшидов О.\nЧепурной С. \nФН11-32");
}

API::~API()
{

    insertForm->close();
    qDebug()<<"destuctor";
    qDebug()<<"destuctor";

    delete connectionForm;
    delete m_Layout;
    qDebug()<<"destuctor";

    delete Lib;
    delete Mat;
    delete Model;
    delete Properties;
    qDebug()<<"destuctor";

    delete localMat;
    delete localModel;
    qDebug()<<"destuctor";

    delete tabLib;
    delete tabMat;
    delete tabModel;
    qDebug()<<"destuctor";

    delete tabProperties;

    delete localTabMat;
    delete localTabModel;
    qDebug()<<"destuctor";

    localDB.close();
    globalDB.close();
    qDebug()<<"destuctor";
    globalDB.removeDatabase("qt_sql_default_connection");
    localDB.removeDatabase("qt_sql_default_connection");
    qDebug()<<"destuctor";
    localDB.~QSqlDatabase();
    globalDB.~QSqlDatabase();
    qDebug()<<"destuctor";

}


