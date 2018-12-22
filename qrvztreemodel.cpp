#include "qrvztreemodel.h"

QRVZTreeModel::QRVZTreeModel(QObject *parent, QString root):QAbstractItemModel(parent){

}

QRVZTreeModel::QRVZTreeModel(QSqlDatabase p_db, QString root){
    this->root = root;
    db = p_db;
    STree = new QSqlQuery();
    STree->exec(QString("SELECT * FROM materialTypes;"));
    STree->first();
    DXc = 0;
}

QVariant QRVZTreeModel::data( const QModelIndex& index, int role) const{
    if(role == Qt::DisplayRole){
        if(index.isValid()){
            STree->seek(index.internalId());
            return STree->value(0);
        }
    }
    return QVariant();
}

QVariant QRVZTreeModel::headerData( int section, Qt::Orientation orientation, int role) const{
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole && section == 0 )
        return QVariant(QString("name_tree"));
    return QVariant();
}

QModelIndex QRVZTreeModel::index( int row, int col, const QModelIndex& index) const{
    int count_chi = 0;
    QString parent = root;
    if(index.isValid()){
        STree->seek(index.internalId());
        parent = STree->value(0).toString();
        STree->first();
        for(int i = 0; i < STree->size(); i++){
            if (STree->value(1).toString() == parent && STree->value(0).toString()!=root){
                if(count_chi == row)return createIndex(row, col, STree->at());
                count_chi++;
            }
            STree->next();
        }
        return QModelIndex();
    }else{
        STree->first();
        for(int i = 0; i < STree->size(); i++){
            if (STree->value(1).toString() == parent){
                if(count_chi == row)return createIndex(row, col, STree->at());
                count_chi++;
            }
            STree->next();
        }
    }
    int a = 0;
    return createIndex(row, col, a);
}

QModelIndex QRVZTreeModel::parent( const QModelIndex& index) const{
    if(index.isValid()){
        STree->seek(index.internalId());
        if(STree->value(0).toString() == root) return QModelIndex();
        QString parent = STree->value(1).toString();
        STree->first();
        for(int i = 0; i < STree->size(); i++){
            if (STree->value(0).toString() == parent){
                QString pid = STree->value(1).toString();
                int rr = 0;
                STree->first();
                for(int j = 0; j < STree->size();j++){
                    if (STree->value(1).toString() == pid){
                        if(STree->value(0).toInt() == parent && STree->value(1).toString() == pid){
                            return createIndex(rr, 0, STree->at());
                        }
                        rr++;
                    }
                    STree->next();
                }
            }
            STree->next();
        }
    }
    return QModelIndex();
}

int QRVZTreeModel::rowCount( const QModelIndex& index) const{
    QString parent = root;
    int count = 0;
    if(index.isValid()){
        STree->seek(index.internalId());
        parent = STree->value(0).toString();
        STree->first();
        for(int i = 0; i<STree->size(); i++ ){
            if(STree->value(1) == parent && STree->value(0)!=root) count++;
            STree->next();
        }
        return count;
    }
    STree->first();
    for(int i = 0; i<STree->size(); i++ ){
        if(STree->value(0) == root) count++;
        STree->next();
    }
    return count;
}

int QRVZTreeModel::columnCount( const QModelIndex& index) const{
    return 1;
}

void QRVZTreeModel::reset(){
    STree->clear();
    STree->exec(QString("SELECT * FROM test.tr ORDER BY tr_id"));
    STree->first();
}
