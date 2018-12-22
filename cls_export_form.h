#ifndef CLS_EXPORT_FORM_H
#define CLS_EXPORT_FORM_H

#include <QObject>
#include <QtWidgets>

class cls_export_form : public QDialog
{
    Q_OBJECT
public:
    explicit cls_export_form(QStringList& lst,QWidget *parent = nullptr);

    QGridLayout layout;
    QLineEdit InputLib;
    QPushButton pbntOK;
    QRadioButton add_libMode;
    QRadioButton not_add_libMode;
    QComboBox libList;
    QStackedWidget stck;
signals:
    void need_AddLib(const QString&);
public slots:
    void slot_choose_mode();
    void slot_pbntOK_clicked();
};

#endif // CLS_EXPORT_FORM_H
