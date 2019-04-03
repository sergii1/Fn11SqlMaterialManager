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
    QSqlDatabase* globalDB;
    QSqlDatabase* localDB;
    explicit cls_insert_form(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent*);
    ~cls_insert_form();
private:
    QStringListModel* model;
    QGridLayout* layout;
    QListWidget* tablesList;
    QLabel* lbl;
    QVector<QLabel*>* columns;
    QVector<QLineEdit*>* inputFields;
    QCommandLinkButton* submit;
    QComboBox* matComboBox;
    QComboBox* modelComboBox;
    QComboBox* propComboBox;
public  slots:
       void elementIsSelected(QListWidgetItem*);
       void insertData();
signals:
    void needUpdateTableView();
    void closed();
};

#endif // CLS_INSERT_FORM_H
