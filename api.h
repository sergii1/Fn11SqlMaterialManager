#ifndef API_H
#define API_H

#include <QtWidgets>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QCommonStyle>
#include <QSqlQuery>
#include <QSqlTableModel>
#include<QList>
#include <QSqlDriver>
#include <QStringListModel>
#include "cls_command_form.h"
#include "cls_connectionform.h"
#include "cls_insert_form.h"
#include "cls_export_form.h"

namespace Ui {
class API;
}


class API : public QMainWindow
{
    Q_OBJECT

public:
    explicit API(QWidget *parent = nullptr);
    bool createConnection();
    QPushButton* createButton(const QString& str);
    ~API();


private:

    cls_connectionForm* connectionForm;
    cls_command_form* command_form;
    cls_insert_form* insert_form;
    cls_export_form* export_form;

    Ui::API *ui;
    QGridLayout* m_Layout;
    QSqlDatabase global_db;
    QSqlDatabase local_db;

    QTreeWidget* Lib;
    QTableView* Mat;
    QTableView* Model;

    QTableView* Properties;

    QDockWidget* tabLib;
    QDockWidget* tabMat;
    QDockWidget* tabModel;
    QDockWidget* tabProperties;

    QTableView* l_Mat;
    QTableView* l_Model;


    QDockWidget* l_tabMat;
    QDockWidget* l_tabModel;

    QListWidget* tables;

    QAction* pactImport;
    QAction* pactExport;
    QAction* pactAddData;
    QAction* pactDeleteMat;
    QAction* pactDeleteModel;
    QAction* pactSQLQuery;

    QString newLib;
    QTextEdit* InputLib;

    bool flagImport;
    bool flagSQLQuery;

    void setColumnWidth();
public slots:
    void slotFormConnection();
    void slotConnection();

    void slotSelectMat();
    void slotSelectModel();
    void slotSelectProperties();
    void slotImport();
    void slotExport();
    void slotLocalSelectModel();
    void slotLocalSelectProperties();

    void slotAddLib(const QString &);

    void slotDeleteMat();
    void slotDeleteModel();

    void slotSQLQuery();

    void slotShowInsertForm();
    void slotCloseInsertForm();

    void createListOfGlobalTable();
    void TabAddToView(QListWidgetItem*);
    void run_command();
    void update_table_view();
signals:
    void connection_is_created();
    void need_update_table_view();
};

#endif // API_H
