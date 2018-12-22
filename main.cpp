#include "api.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    API w;
    w.showMaximized();
    return a.exec();
}
