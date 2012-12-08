#include "storage/st_respawncontainer.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TRespawnContainer::TRespawnContainer(QObject* parent)
    : QObject(parent)
    , TTContainer()
{
}
//------------------------------------------------------------------------------
TRespawnContainer::TRespawnContainer(const TRespawnContainer& container)
    : QObject(container.parent())
    , TTContainer(container)
{
}
//------------------------------------------------------------------------------
TRespawnContainer& TRespawnContainer::operator =(const TRespawnContainer& container)
{
    TTContainer::operator =(container);
    return *this;
}
//------------------------------------------------------------------------------
TRespawnContainer::TRespawnItemId TRespawnContainer::addRespawn(
        const TRespawnInfo& info)
{
    TRespawnItem item(info);
    return addItem(item);
}
//------------------------------------------------------------------------------
TRespawnContainer::TRespawnItemId TRespawnContainer::addRespawn(
        const TRespawnItem& item)
{
    return addItem(item);
}
//------------------------------------------------------------------------------
void TRespawnContainer::removeRespawn(const TRespawnItem& item)
{
    removeItem(item);
}
//------------------------------------------------------------------------------
void TRespawnContainer::removeRespawn(TRespawnItemId id)
{
    removeItem(id);
}
//------------------------------------------------------------------------------
void TRespawnContainer::loadRespawnList(const QString& respawnList,
        const QDir& baseDirectory)
{
    // TODO: Make usage of baseDirectory
    Q_UNUSED(baseDirectory);

    QFile file(respawnList);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(respawnList));
    }
    QTextStream stream(&file);
    TRespawnItem item;
    while (!stream.atEnd()) {
        if (!item.unpack(stream.readLine())) {
            continue;
        }
        item.setResourceFile(respawnList);
        addRespawn(item);
    }
    file.close();
}
//------------------------------------------------------------------------------
void TRespawnContainer::saveRespawnList(const QString& respawnList,
        const QDir& baseDirectory) const
{
    // TODO: Make usage of baseDirectory
    Q_UNUSED(baseDirectory);

    QFile file(respawnList);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(respawnList));
    }
    QTextStream stream(&file);
    auto it = constBegin();
    for ( ; it != constEnd(); ++it )
    {
        const TRespawnItem& respawn = (*it);
        if( !respawn.isValid() )
            continue;

        stream << respawn.pack() << "\n";
    }
    file.close();
}
//------------------------------------------------------------------------------
