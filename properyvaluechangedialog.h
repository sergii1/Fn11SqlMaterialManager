#ifndef PROPERYVALUECHANGEDIALOG_H
#define PROPERYVALUECHANGEDIALOG_H

#include <QDialog>

namespace Ui {
class ProperyValueChangeDialog;
}

class ProperyValueChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProperyValueChangeDialog(QWidget *parent = nullptr);
    ~ProperyValueChangeDialog();
    static float getValue();
    static bool needUpdate;

private slots:
    void on_pushButton_clicked();

private:
    static float propertyValue;
    Ui::ProperyValueChangeDialog *ui;
};

#endif // PROPERYVALUECHANGEDIALOG_H
