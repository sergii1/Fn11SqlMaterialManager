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
    QDockWidget* dck_formConnection;
    QVBoxLayout* m_VLayout;
    QPushButton* pbtnConnect;
};
#endif // CLS_CONNECTIONFORM_H
