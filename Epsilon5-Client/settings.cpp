#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "settings.h"

TSettings::TSettings(QObject *parent)
    : USettings(parent)
{
    // TODO: Rewrite this function
    //CheckIniFile();
    Load("settings.ini");
}

void TSettings::CheckIniFile(){
    // Length: 59 / 0x0000003B (bytes)
    unsigned char rawData[59] =
    {
        0x6E, 0x69, 0x63, 0x6B, 0x6E, 0x61, 0x6D, 0x65, 0x3D, 0x62, 0x61, 0x6B, 0x0D, 0x0A, 0x73, 0x65,
        0x72, 0x76, 0x65, 0x72, 0x2E, 0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x31, 0x32, 0x37,
        0x2E, 0x30, 0x2E, 0x30, 0x2E, 0x31, 0x0D, 0x0A, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2E, 0x70,
        0x6F, 0x72, 0x74, 0x3D, 0x31, 0x34, 0x35, 0x36, 0x37, 0x0D, 0x0A,
    } ;

    QFile IniFile("settings.ini");
    if (IniFile.open(QIODevice::WriteOnly)) {
        qint64 bytesWritten = IniFile.write(reinterpret_cast<const char*>(rawData), sizeof(rawData));
                if (bytesWritten < sizeof(rawData)) {
                    //error here
                }
                IniFile.close();
            }
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
