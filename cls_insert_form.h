#ifndef CLS_INSERT_FORM_H
#define CLS_INSERT_FORM_H

#include <QObject>
#include <QtWidgets>
#include <QSqlDatabase>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
class cls_insert_form: public QDialog{
   Q_OBJECT
public:
    QSqlDatabase* global_db;
    QSqlDatabase* local_db;
    explicit cls_insert_form(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent*);
    ~cls_insert_form();
private:
    QStringListModel* model;
    QGridLayout* layout;
    QListWidget* tbl_list;
    QLabel* lbl;
    QVector<QLabel*>* columns;
    QVector<QLineEdit*>* input_fields;
    QCommandLinkButton* submit;
    QComboBox* matComboBox;
    QComboBox* modelComboBox;
    QComboBox* propComboBox;
public  slots:
       void element_is_selected(QListWidgetItem*);
       void insert_data();
signals:
    void need_update_table_view();
    void closed();
};

#endif // CLS_INSERT_FORM_H
