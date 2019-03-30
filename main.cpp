#include "api.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << argc;
    for(int i =0; i < argc; ++i)
        qDebug() << argv[i];
    API w;
    w.resize(800,900);
    w.show();
    return a.exec();
}
