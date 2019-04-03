#ifndef CLS_EXPORT_FORM_H
#define CLS_EXPORT_FORM_H

#include <QObject>
#include <QtWidgets>

class cls_export_form : public QDialog
{
    Q_OBJECT
public:
    explicit cls_export_form(QStringList& lst,QWidget *parent = nullptr);
private:
    QGridLayout layout;
    QLineEdit InputLib;
    QPushButton pbntOK;
    QRadioButton addLibMode;
    QRadioButton notAddLibMode;
    QComboBox libList;
    QStackedWidget stck;
signals:
    void needAddLib(const QString&);
public slots:
    void slot_ChooseMode();
    void slot_pbntOkClicked();
};

#endif // CLS_EXPORT_FORM_H
