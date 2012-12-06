// maprespawncontainer.cpp
#include <QFile>
#include <QTextStream>
#include "containers/maprespawncontainer.h"
#include "../utils/uexception.h"
//------------------------------------------------------------------------------
TMapRespawnContainer::TMapRespawnContainer(QObject* parent)
//    : TContainer(parent)
//    : QStandardItemModel(parent)
    : QObject(parent)
    , mModel(new QStandardItemModel(this))
{
}
//------------------------------------------------------------------------------
TMapRespawnContainer::~TMapRespawnContainer()
{
}
//------------------------------------------------------------------------------
QStandardItemModel* TMapRespawnContainer::model()
{
    return mModel;
}
//------------------------------------------------------------------------------
void TMapRespawnContainer::addRespawn(const TMapRespawnInfo& info)
{
//    TMapRespawnItem* item = new TMapRespawnItem(info);
    QStandardItem* item = new QStandardItem();
    item->setData(QVariant::fromValue(info));
    mModel->appendRow(item);
//    appendRow(item);
}
//------------------------------------------------------------------------------
//void TMapRespawnContainer::removeRespawn(const TMapRespawnItem& item)
//{
//    mModel->removeRow(item.row());
////    removeRow(item.row());
//}
//------------------------------------------------------------------------------
void TMapRespawnContainer::removeRespawn(const QModelIndex &index)
{
    mModel->removeRow(index.row());
//    removeRow(index.row())
}
//------------------------------------------------------------------------------
void TMapRespawnContainer::loadFromFile(const QString &fileName)
{
    QFile file(fileName, this);
    if( !file.open(QFile::ReadOnly | QFile::Text) ) {
        throw UException(QString(Q_FUNC_INFO)
            .append(":: open file error: '%1'").arg(fileName));
    }

    QTextStream stream(&file);
    TMapRespawnInfo info;
    while( !stream.atEnd() )
    {
        if( !info.unpack(stream.readLine()) )
        {
            qDebug( "%s :: Ingonring...", Q_FUNC_INFO );
            continue;
        }

        addRespawn(info);
    }
    file.close();
}
//------------------------------------------------------------------------------
//TMapRespawnItem* TMapRespawnContainer::item(int row, int column) const
//{
//    return (TMapRespawnItem*)(TContainer::item(row, column));
//}
//------------------------------------------------------------------------------
void TMapRespawnContainer::saveToFile(const QString &fileName)
{
    QFile file(fileName, this);
    if( !file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text) ) {
        throw UException(QString(Q_FUNC_INFO)
            .append(":: open file error: '%1'").arg(fileName));
    }

    QTextStream stream(&file);
    QString line;
    for( int i = 0; i < mModel->rowCount(); ++i ) {
        stream << mModel->item(i)->data().value<TMapRespawnItem>().respawnInfo().pack() << "\n";
    }
    file.close();
}
//------------------------------------------------------------------------------
