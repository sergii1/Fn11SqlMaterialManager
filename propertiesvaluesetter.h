#ifndef PROPERTIESVALUESETTER_H
#define PROPERTIESVALUESETTER_H

#include <QDialog>
#include <QtWidgets>
namespace Ui {
class PropertiesValueSetter;
}

class PropertiesValueSetter : public QDialog
{
    Q_OBJECT

public:
    explicit PropertiesValueSetter(QWidget *parent = nullptr);
    ~PropertiesValueSetter();
    QComboBox* getComboBox1();
    QLabel* getLabel();
    QDoubleSpinBox* getSpinBox();
    static QString getField1();
    static QString getField2();
    static double getValue();
    static bool needSetValue;
private slots:
    void on_pushButton_clicked();

private:
    static QString field1;
    static QString field2;
    static double value;
    Ui::PropertiesValueSetter *ui;
};

#endif // PROPERTIESVALUESETTER_H
