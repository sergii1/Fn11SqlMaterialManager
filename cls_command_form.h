#ifndef CLS_COMMAND_FORM_H
#define CLS_COMMAND_FORM_H

#include <QObject>
#include <QWidget>
#include <QDockWidget>
#include <QTextEdit>
#include <QLabel>
#include <QCommandLinkButton>
#include <QRadioButton>
#include <QGridLayout>
#include <QDebug>

class cls_command_form: public QWidget{
    public:
    cls_command_form(QWidget* ptr, QWidget *parent = nullptr);
    ~cls_command_form();
    QDockWidget* dck_command_wdgt;
    QTextEdit* command_text;
    QLabel* command_res;
    QCommandLinkButton* submit;
    QRadioButton* rb_localDb;
    QRadioButton* rb_globalDb;

};

#endif // CLS_COMMAND_FORM_H
