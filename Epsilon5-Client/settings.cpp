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
