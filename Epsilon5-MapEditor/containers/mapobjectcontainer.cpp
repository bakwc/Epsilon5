// mapobjectcontainer.cpp
#include <QFile>
#include <QTextStream>
#include "containers/mapobjectcontainer.h"
#include "../utils/uexception.h"
//------------------------------------------------------------------------------
TMapObjectContainer::TMapObjectContainer(QObject* parent)
    : TContainer(parent)
{
}
//------------------------------------------------------------------------------
TMapObjectContainer::TMapObjectContainer(const TMapObjectContainer &container)
    : TContainer(container.parent())
{
}
//------------------------------------------------------------------------------
TMapObjectContainer::~TMapObjectContainer()
{
}
//------------------------------------------------------------------------------
void TMapObjectContainer::addObject(const TMapObjectInfo &info)
{
    QStandardItem* item = new QStandardItem;
    TMapObjectItem* object = new TMapObjectItem(info);
    item->setData(QVariant::fromValue(*object));
    item->setText(object->serialize());
    item->setEditable(false);
    mModel->appendRow(item);
}
//------------------------------------------------------------------------------
void TMapObjectContainer::removeObject(const QModelIndex &index)
{
    mModel->removeRow(index.row());
}
//------------------------------------------------------------------------------
void TMapObjectContainer::loadFromFile(const QString &fileName)
{
    QFile file(fileName, this);
    if( !file.open(QFile::ReadOnly | QFile::Text) ) {
        throw UException(QString(Q_FUNC_INFO)
            .append(":: open file error: '%1'").arg(fileName));
    }

    QTextStream stream(&file);
    TMapObjectInfo info;
    while( !stream.atEnd() )
    {
        if( !info.unpack(stream.readLine()) )
            continue;

        addObject(info);
    }
    file.close();
}
//------------------------------------------------------------------------------
void TMapObjectContainer::saveToFile(const QString &fileName)
{
    QFile file(fileName, this);
    if( !file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text) ) {
        throw UException(QString(Q_FUNC_INFO)
            .append(":: open file error: '%1'").arg(fileName));
    }

    QTextStream stream(&file);
    for( int i = 0; i < mModel->rowCount(); ++i ) {
        stream << mModel->item(i)->data()
            .value<TMapObjectItem>().objectInfo().pack() << "\n";
    }
    file.close();
}
//------------------------------------------------------------------------------
