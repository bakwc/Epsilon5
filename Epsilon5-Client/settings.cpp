#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "settings.h"

TSettings::TSettings(QObject* parent)
    : USettings(parent) {
    // TODO: Rewrite this function
    CheckIniFile(); //If file doesn't exist, create it with default settings
    Load("settings.ini");
}

void TSettings::CheckIniFile() {
    QFile IniFile("settings.ini");
    if (!IniFile.exists()) {
        if (IniFile.open(QIODevice::WriteOnly)) {
            QTextStream stream(&IniFile);
            stream << "nickname=bak\r" << endl;
            stream << "server.address=127.0.0.1\r" << endl;
            stream << "server.port=14567" << endl;
            IniFile.close();
        }
    }
}

QString TSettings::GetNickname() {
    return GetParameter("nickname");
}

QString TSettings::GetServerAddr() {
    return GetParameter("server.address");
}

quint16 TSettings::GetServerPort() {
    return GetParameter("server.port");
}
