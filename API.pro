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
    treeitem.cpp \
    dialog.cpp \
    mytablewidget.cpp \
    mytreewidget.cpp \
    correlatedialog.cpp \
    propertiesvaluesetter.cpp \
    connectiondialog.cpp \
    helpbrowser.cpp

HEADERS  += api.h \
    cls_connectionform.h \
    cls_insert_form.h \
    cls_export_form.h \
    sh_tree.h \
    treeitem.h \
    dialog.h \
    mytablewidget.h \
    mytreewidget.h \
    correlatedialog.h \
    propertiesvaluesetter.h \
    connectiondialog.h \
    helpbrowser.h

FORMS    += \
    dialog.ui \
    mytablewidget.ui \
    mytreewidget.ui \
    correlatedialog.ui \
    propertiesvaluesetter.ui \
    connectiondialog.ui

RESOURCES += \
    resources.qrc
