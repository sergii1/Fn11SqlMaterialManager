#include "api.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    api w;
    w.show();

    return a.exec();
}
