#include "cls_libtreeitem.h"

cls_LibTreeItem::cls_LibTreeItem(const QList<QVariant> &data, cls_LibTreeItem* parent)
{
    m_parentItem = parent;
    m_itemData = data;
}

cls_LibTreeItem::~cls_LibTreeItem()
{
    qDeleteAll(m_childItems);
}

void cls_LibTreeItem::appendChild(cls_LibTreeItem *item)
{
    m_childItems.append(item);
}

cls_LibTreeItem *cls_LibTreeItem::child(int row)
{
    return m_childItems.value(row);
}

int cls_LibTreeItem::childCount() const
{
    return m_childItems.count();
}

int cls_LibTreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<cls_LibTreeItem*>(this));

    return 0;
}

int cls_LibTreeItem::columnCount() const
{
    return m_itemData.count();
}

QVariant cls_LibTreeItem::data(int column) const
{
    return m_itemData.value(column);
}

cls_LibTreeItem *cls_LibTreeItem::parentItem()
{
    return m_parentItem;
}
