#ifndef CORRELATEDIALOG_H
#define CORRELATEDIALOG_H

#include <QDialog>
#include <QtWidgets>
namespace Ui {
class CorrelateDialog;
}

class CorrelateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CorrelateDialog(QWidget *parent = nullptr);
    ~CorrelateDialog();
    QLabel* getLabel1();
    QLabel* getLabel2();
    QComboBox* getComboBox1();
    QComboBox* getComboBox2();
    static QString getField1();
    static QString getField2();
    static bool needCorrelate;
private slots:
    void on_pushButton_clicked();

private:
    static QString field1;
    static QString field2;

    Ui::CorrelateDialog *ui;
};

#endif // CORRELATEDIALOG_H
