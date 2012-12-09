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
void TRespawnContainer::loadRespawnList(const QString& respawnList)
{
    clearItems();

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
        addItem(item);
    }
    file.close();
}
//------------------------------------------------------------------------------
void TRespawnContainer::saveRespawnList(const QString& respawnList) const
{
    QFile file(respawnList);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(respawnList));
    }
    QTextStream stream(&file);
    auto it = constBegin();
    for (; it != constEnd(); ++it) {
        const TRespawnItem& respawn = (*it);
        if (!respawn.isValid()) {
            continue;
        }

        stream << respawn.pack() << "\n";
    }
    file.close();
}
//------------------------------------------------------------------------------
