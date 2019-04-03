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
#include "cls_command_form.h"
#include "cls_connectionform.h"
#include "cls_insert_form.h"
#include "cls_export_form.h"
#include "sh_tree.h"

namespace Ui {
class API;
}


class API : public QMainWindow
{
    Q_OBJECT

public:
    explicit API(const QString& pathToDB,QWidget *parent = nullptr);
    bool createConnection();
    QPushButton* createButton(const QString& str);
    ~API();


private:

    cls_connectionForm* connectionForm;
    cls_command_form* commandForm;
    cls_insert_form* insertForm;
    cls_export_form* exportForm;

    Ui::API *ui;
    QGridLayout* m_Layout;
    QSqlDatabase globalDB;
    QSqlDatabase local_db;

    QTreeView* Tree;
    QTreeWidget* Lib;
    QTableView* Mat;
    QTableView* Model;

    QTableView* Properties;

    QDockWidget* tabLib;
    QDockWidget* tabMat;
    QDockWidget* tabModel;
    QDockWidget* tabProperties;

    QTableView* localMat;
    QTableView* localModel;


    QDockWidget* localTabMat;
    QDockWidget* localTabModel;

    QListWidget* tables;

    QAction* pactImport;
    QAction* pactExport;
    QAction* pactAddData;
    QAction* pactDeleteMat;
    QAction* pactDeleteModel;
    QAction* pactSQLQuery;
    QAction* pactFAQ;

    QString newLib;
    QTextEdit* InputLib;

    bool flagImport;
    bool flagSQLQuery;

    void setColumnWidth();
    QString getFullPath(const QModelIndex& index);
    QString getScheme(const QString& path);
public slots:

    void slotMyContextMenu(const QPoint&);

    void slot_AddClassification();
    void slot_AddBranch();
    void slot_AddMaterial();
    void slot_RemoveClassification();
    void slot_RemoveBranch();

    void slot_FormConnection();
    void slot_Connection();

    void slot_SelectMat();
    void slot_SelectModel();
    void slot_SelectProperties();
    void slot_Import();
    void slotExport();
    void slotLocalSelectModel();
    void slotLocalSelectProperties();

    void slot_AddLib(const QString &);

    void slot_DeleteMat();
    void slot_DeleteModel();

    void slot_SQLQuery();

    void slot_ShowInsertForm();
    void slot_CloseInsertForm();

    void slot_CreateListOfGlobalTable();
    void slot_TabAddToView(QListWidgetItem*);
    void slot_RunCommand();
    void slot_UpdateTableView();

    void slot_About();
signals:
    void connection_is_created();
    void need_update_table_view();
};

#endif // API_H
