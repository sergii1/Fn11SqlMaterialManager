#include "api.h"
#include <QApplication>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << argc;
    for(int i =0; i < argc; ++i){
        qDebug() << argv[i];
    }
    QString path = argv[argc-1];

    qDebug()<<"path"<<path;
    auto it= path.end()-1;
    for(it = path.end()-1; *it!='.';--it){
        *it = '\0';
    }
    it++;
    *it='d';
    it++;
    *it ='b'; //SMCMP
    qDebug()<<"path"<<path;
    API w(path);
    QDesktopWidget dsk;
    QSize size = dsk.availableGeometry().size();
    size.setHeight(size.height()-45);
    w.resize(size);
    w.show();
    return a.exec();
}
