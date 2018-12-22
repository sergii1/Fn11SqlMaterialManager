#ifndef QRVZTREEMODEL_H
#define QRVZTREEMODEL_H

#include <QAbstractItemModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QDebug>

class QRVZTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit QRVZTreeModel(QObject *parent = 0, QString root = QString());
    explicit QRVZTreeModel(QSqlDatabase , QString root = QString());
    QString root;

    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
    //Qt::ItemFlags flags( const QModelIndex& index ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    QModelIndex index( int row, int col, const QModelIndex& index = QModelIndex() ) const;
    QModelIndex parent( const QModelIndex& index ) const;
    int rowCount( const QModelIndex& index = QModelIndex() ) const;
    int columnCount( const QModelIndex& index = QModelIndex() ) const;
    void reset();
    void inc(){DXc++;qDebug()<<"DX - "<<DXc;}

private:
    QSqlDatabase db;
    QSqlQuery *STree;
    int DXc;

signals:

public slots:

};


#endif // QRVZTREEMODEL_H
