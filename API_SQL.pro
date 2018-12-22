#-------------------------------------------------
#
# Project created by QtCreator 2018-12-22T22:18:42
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = API_SQL
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        api.cpp \
    cls_command_form.cpp \
    cls_connectionform.cpp \
    cls_export_form.cpp \
    cls_insert_form.cpp \
    cls_libtreeitem.cpp \
    main.cpp \
    qrvztreemodel.cpp

HEADERS += \
        api.h \
    cls_command_form.h \
    cls_connectionform.h \
    cls_export_form.h \
    cls_insert_form.h \
    cls_libtreeitem.h \
    labtreemodel.h \
    qrvztreemodel.h

FORMS += \
        api.ui \

RESOURCES += \
    icons.qrc
