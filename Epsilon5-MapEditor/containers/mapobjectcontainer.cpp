// mapobjectcontainer.cpp
#include <QFile>
#include <QTextStream>
#include "containers/mapobjectcontainer.h"
#include "../utils/uexception.h"
//------------------------------------------------------------------------------
using namespace oldcontainers;
//------------------------------------------------------------------------------
TMapObjectContainer::TMapObjectContainer(QObject* parent)
    : TContainer(parent)
{
}
//------------------------------------------------------------------------------
TMapObjectContainer::TMapObjectContainer(const TMapObjectContainer& container)
    : TContainer(container)
{
}
//------------------------------------------------------------------------------
TMapObjectContainer::~TMapObjectContainer()
{
}
//------------------------------------------------------------------------------
TMapObjectContainer& TMapObjectContainer::operator =(
    const TMapObjectContainer& container)
{
    return TMapObjectContainer::operator =(container);
}
//------------------------------------------------------------------------------
void TMapObjectContainer::addObject(const TMapObjectInfo& info)
{
    QStandardItem* item = new QStandardItem;
    TMapObjectItem* object = new TMapObjectItem(info);
    item->setData(QVariant::fromValue(*object));
    item->setText(object->serialize());
    item->setEditable(false);
    mModel->appendRow(item);
    ++mLastValidId;
}
//------------------------------------------------------------------------------
void TMapObjectContainer::removeObject(const QModelIndex& index)
{
    mModel->removeRow(index.row());
}
//------------------------------------------------------------------------------
void TMapObjectContainer::loadFromFile(const QString& fileName)
{
    QFile file(fileName, this);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(fileName));
    }
    QTextStream stream(&file);
    TMapObjectInfo info;
    while (!stream.atEnd()) {
        if (!info.unpack(stream.readLine())) {
            continue;
        }
        addObject(info);
    }
    file.close();
}
//------------------------------------------------------------------------------
void TMapObjectContainer::saveToFile(const QString& fileName)
{
    QFile file(fileName, this);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(fileName));
    }
    QTextStream stream(&file);
    for (int i = 0; i < mModel->rowCount(); ++i) {
        const TMapObjectItem& object = mModel->item(i)->data()
                .value<TMapObjectItem>();
        if (!object.isValid()) {
            continue;
        }
        stream << object.serialize() << "\n";
    }
    file.close();
}
//------------------------------------------------------------------------------
qint32 TMapObjectContainer::x(const QModelIndex& index) const
{
    const QStandardItem* item = mModel->itemFromIndex(index);
    return item->data().value<TMapObjectItem>().objectInfo()->x;
}
//------------------------------------------------------------------------------
qint32 TMapObjectContainer::y(const QModelIndex& index) const
{
    const QStandardItem* item = mModel->itemFromIndex(index);
    return item->data().value<TMapObjectItem>().objectInfo()->y;
}
//------------------------------------------------------------------------------
qreal TMapObjectContainer::angle(const QModelIndex& index) const
{
    const QStandardItem* item = mModel->itemFromIndex(index);
    return item->data().value<TMapObjectItem>().objectInfo()->angle;
}
//------------------------------------------------------------------------------
quint32 TMapObjectContainer::id(const QModelIndex& index) const
{
    const QStandardItem* item = mModel->itemFromIndex(index);
    return item->data().value<TMapObjectItem>().objectInfo()->id;
}
//------------------------------------------------------------------------------
void TMapObjectContainer::setX(const QModelIndex& index, qint32 x)
{
    QStandardItem* item = mModel->itemFromIndex(index);
    const TMapObjectItem& objectItem = item->data().value<TMapObjectItem>();
    objectItem.objectInfo()->x = x;
    item->setData(QVariant::fromValue(objectItem));
    item->setText(objectItem.objectInfo()->pack());
}
//------------------------------------------------------------------------------
void TMapObjectContainer::setY(const QModelIndex& index, qint32 y)
{
    QStandardItem* item = mModel->itemFromIndex(index);
    const TMapObjectItem& objectItem = item->data().value<TMapObjectItem>();
    objectItem.objectInfo()->y = y;
    item->setData(QVariant::fromValue(objectItem));
    item->setText(objectItem.objectInfo()->pack());
}
//------------------------------------------------------------------------------
void TMapObjectContainer::setAngle(const QModelIndex& index, qreal angle)
{
    QStandardItem* item = mModel->itemFromIndex(index);
    const TMapObjectItem& objectItem = item->data().value<TMapObjectItem>();
    objectItem.objectInfo()->angle = angle;
    item->setData(QVariant::fromValue(objectItem));
    item->setText(objectItem.objectInfo()->pack());
}
//------------------------------------------------------------------------------
void TMapObjectContainer::setId(const QModelIndex& index, quint32 id)
{
    QStandardItem* item = mModel->itemFromIndex(index);
    const TMapObjectItem& objectItem = item->data().value<TMapObjectItem>();
    objectItem.objectInfo()->id = id;
    item->setData(QVariant::fromValue(objectItem));
    item->setText(objectItem.objectInfo()->pack());
}
//------------------------------------------------------------------------------
