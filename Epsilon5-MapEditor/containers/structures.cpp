#include <QStringList>
#include "containers/structures.h"
//------------------------------------------------------------------------------
QString TMapRespawnInfo::pack()
{
    return QString("%1:%2:%3:%4:%5:%6:%7:%8").arg(x).arg(y).arg(captureRadius)
            .arg(spawnRadius).arg(isCapturable)
            .arg(isMain).arg(captureTime).arg(team);
}
//------------------------------------------------------------------------------
bool TMapRespawnInfo::unpack(const QString &string)
{
    const quint8 STRUCTURE_FIELDS_COUNT = 8;
    QStringList vars = string.split(":");
    bool isOk;
    if( vars.count() != STRUCTURE_FIELDS_COUNT ) {
        return false;
    }
    x = vars[0].toInt(&isOk);
    if( !isOk ) return false;
    y = vars[1].toInt(&isOk);
    if( !isOk ) return false;
    captureRadius = vars[2].toUInt(&isOk);
    if( !isOk ) return false;
    spawnRadius = vars[3].toUInt(&isOk);
    if( !isOk ) return false;
    isCapturable = (bool) vars[4].toUInt(&isOk);
    if( !isOk ) return false;
    isMain = (bool) vars[5].toUInt(&isOk);
    if( !isOk ) return false;
    captureTime = vars[6].toUInt(&isOk);
    if( !isOk ) return false;
    team = (ETeam) (vars[7].toUInt(&isOk) % ETEAM_SIZE);
    if( !isOk ) return false;

    return true;
}
//------------------------------------------------------------------------------
