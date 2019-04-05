#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
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

    static QString getName();
    static QString getDescription();
    static bool needInsert;
    static QString name;
    static QString description;

private slots:
    void on_buttonBox_2_accepted();


private:

    Ui::Dialog *ui;
    QStringList F(bool flag);
};

#endif // DIALOG_H
