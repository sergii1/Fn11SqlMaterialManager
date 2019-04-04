#-------------------------------------------------
#
# Project created by QtCreator 2018-11-27T11:51:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = API
TEMPLATE = app


SOURCES += main.cpp\
        api.cpp \
    cls_connectionform.cpp \
    cls_insert_form.cpp \
    cls_export_form.cpp \
    sh_tree.cpp \
    treeitem.cpp

HEADERS  += api.h \
    cls_connectionform.h \
    cls_insert_form.h \
    cls_export_form.h \
    sh_tree.h \
    treeitem.h

FORMS    += api.ui

RESOURCES += \
    resources.qrc
