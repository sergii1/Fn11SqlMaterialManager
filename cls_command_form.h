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

    QTextEdit* commandText;
    QLabel* command_res;
    QDockWidget* dock_CommandWdgt;
    QRadioButton* rb_globalDB;
    private:
    QCommandLinkButton* submit;
    QRadioButton* rb_LocalDB;
};

#endif // CLS_COMMAND_FORM_H
