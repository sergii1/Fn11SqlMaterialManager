#ifndef API_H
#define API_H

#include <QtWidgets>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QCommonStyle>
#include <QListWidget>
#include <QTableView>
#include <QSqlQuery>
#include <QTreeWidget>
#include <QCommandLinkButton>
#include <QSqlTableModel>
#include <QTreeWidgetItem>
#include<QList>
#include <QSqlDriver>
#include <QStringListModel>
#include "cls_connectionform.h"
#include "cls_insert_form.h"
#include "cls_export_form.h"
#include "sh_tree.h"
#include "dialog.h"
#include "mytablewidget.h"
#include "mytreewidget.h"

class API : public QMainWindow
{
    Q_OBJECT

public:
    explicit API(const QString& pathToDB,QWidget *parent = nullptr);
    QPushButton* createButton(const QString& str);
    ~API();


private:
    QString nameMaterial;

    cls_connectionForm* connectionForm;
    cls_insert_form* insertForm;
    cls_export_form* exportForm;

    QGridLayout* m_Layout;
    QSqlDatabase globalDB;
    QSqlDatabase localDB;

    QTreeView* Tree;
    QTreeWidget* classification;
    QTableView* materials;
    QTableView* Model;
    QTableView* Properties;
    QTableView* localMat;
    QTableView* localModel;

    //пробую заменить tabMat на MaterialTable
    MyTableWidget* materialTable;
    MyTableWidget* modelTable;
    MyTableWidget* propertiesTable;
    MyTableWidget* localMaterialTable;
    MyTableWidget* localModelTable;
    MyTreeWidget* classificationTree;


    QAction* pactImport;
    QAction* pactExport;
    QAction* pactAddData;
    QAction* pactDeleteMat;
    QAction* pactDeleteModel;
    QAction* pactSQLQuery;
    QAction* pactFAQ;

    //QActioin которыые используются в дереве
    QAction* pAct_tree_add_branch;
    QAction* pAct_tree_remove_branch;
    QAction* pAct_tree_add_classification;
    QAction* pAct_tree_remove_classification;
    QAction* pAct_tree_add_material;

    QString newLib;
    QTextEdit* InputLib;

    bool flagImport;
    bool flagSQLQuery;

    void setColumnWidth();
    QString getFullPath(const QModelIndex& index);
    QString getScheme(const QString& path);
    void initTree();
    void initLocalDb(const QString& pathToDB);
    void initBody();
    void initMenu();
public slots:

    void slot_TreeContextMenu(const QPoint&);
    void slot_MatContextMenu(const QPoint&);
    void slot_ModelContextMenu(const QPoint&);
    void slot_PropertiesContextMenu(const QPoint&);

    void slot_Local_MatContextMenu(const QPoint&);
    void slot_Local_ModelContextMenu(const QPoint&);

    //cлоты к контекстному меню дерева
    void slot_AddClassification();
    void slot_AddBranch();
    void slot_AddMaterial();
    void slot_RemoveClassification();
    void slot_RemoveBranch();

    //слоты к остальным представлениям
    void slot_local_add_model();
    void slot_local_add_mat();
    void slot_add_properties();
    void slot_add_model();
    void slot_add_material();

    void slot_createConnectionDialog();
    void slot_createConnection();

    void slot_SelectMat();
    void slot_SelectModel();
    void slot_SelectProperties();
    void slot_Import();
    void slot_Export();
    void slot_LocalSelectModel();
    void slot_LocalSelectProperties();

    void slot_AddLib(const QString &);

    void slot_DeleteMat();
    void slot_DeleteModel();

    void slot_ShowInsertForm();
    void slot_CloseInsertForm();

    void slot_UpdateTableView();

    void slot_About();
signals:
    void connectionIsCreated();
    void needUpdateTableView();
};

#endif // API_H
