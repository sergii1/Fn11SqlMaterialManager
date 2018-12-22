#ifndef CLS_LIBTREEITEM_H
#define CLS_LIBTREEITEM_H
#include <QList>

class cls_LibTreeItem
{
public:
    explicit cls_LibTreeItem(const QList<QVariant> &data, cls_LibTreeItem *parentItem = 0);
    ~cls_LibTreeItem();

    void appendChild(cls_LibTreeItem *child);

    cls_LibTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    cls_LibTreeItem *parentItem();

private:
    QList<cls_LibTreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    cls_LibTreeItem *m_parentItem;
};

#endif // CLS_LIBTREEITEM_H
