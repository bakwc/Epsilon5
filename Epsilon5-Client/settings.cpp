#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "settings.h"

TSettings::TSettings(QObject *parent)
    : USettings(parent)
{
    Load("settings.ini");
}

QString TSettings::GetNickname() {
    return GetParameter("nickname");
}

QString TSettings::GetServerAddr() {
    return GetParameter("server.address").trimmed();
}

quint16 TSettings::GetServerPort() {
    return GetParameter("server.port").toUInt();
}
