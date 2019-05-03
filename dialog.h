#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <QStringList>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QLabel* getLabel1();
    QLabel* getLabel2();
    QLineEdit* getLineEdit1();
    QLineEdit* getLineEdit2();
    static QString getName();
    static QString getDescription();
    static bool needInsert;

private slots:
    void on_buttonBox_2_accepted();


    void on_buttonBox_2_rejected();

private:
    static QString name;
    static QString description;
    Ui::Dialog *ui;
    QStringList F(bool flag);
};

#endif // DIALOG_H
