#ifndef CLS_CONNECTIONFORM_H
#define CLS_CONNECTIONFORM_H

#include <QObject>
#include <QtWidgets>


class cls_connectionForm: public QDialog{
public:
    explicit cls_connectionForm(QWidget *parent = nullptr);
    QLineEdit* nameDB;
    QLineEdit* nameUser;
    QLineEdit* Host;
    QLineEdit* Port;
    QLineEdit* Password;
    QPushButton* pbtnConnect;
private:
    QDockWidget* dock_FormConnection;
    QVBoxLayout* vLayout;
};
#endif // CLS_CONNECTIONFORM_H
