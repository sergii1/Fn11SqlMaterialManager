#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtWidgets>
#include <QSqlError>
namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QSqlDatabase* p_db, QWidget *parent = nullptr);
    ~ConnectionDialog();

    QPushButton* get_btn_globalConnect();
    QString getNameDB();
    QString getUserName();
    QString getHost();
    int getPort();
    QString getPassword();

private slots:

    void on_rb_global_clicked();

    void on_rb_local_clicked();

private:

    QSqlDatabase* db;
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTIONDIALOG_H
