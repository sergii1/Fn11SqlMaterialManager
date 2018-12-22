#ifndef API_H
#define API_H

#include <QMainWindow>

namespace Ui {
class api;
}

class api : public QMainWindow
{
    Q_OBJECT

public:
    explicit api(QWidget *parent = 0);
    ~api();

private:
    Ui::api *ui;
};

#endif // API_H
