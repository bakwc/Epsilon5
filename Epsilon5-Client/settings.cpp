#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "settings.h"
#include <windows.h>
#include <winsock2.h>


const char* SETTINGS_FILENAME = "settings.ini";
const char* DEFAULT_PLAYER_NAME = "player";
const char* DEFAULT_SERVER_ADDRESS = "127.0.0.1";
const quint16 DEFAULT_SERVER_PORT = 14567;
const bool DEFAULT_WINDOW_FULLSCREEN = true;

TSettings::TSettings(QObject* parent)
    : QObject(parent)
    , Settings(new USettings(this))
{
    // Define default parameters
    USettings::TParametersHash params;
    params["nickname"] = QString(DEFAULT_PLAYER_NAME);
    params["server.address"] = QString(DEFAULT_SERVER_ADDRESS);
    params["server.port"] = QString().number(DEFAULT_SERVER_PORT);
    params["window.fullscreen"] = QString().number(DEFAULT_WINDOW_FULLSCREEN);
    Settings->DefineParams(params);
    Load();
}

TSettings::~TSettings()
{
    Save();
}

QString TSettings::GetNickname() {
    return Settings->GetParameter("nickname");
}

QString TSettings::GetServerAddr() {
    QString serverAddr = Settings->GetParameter("server.address");
#ifdef Q_OS_WIN32
    WSADATA wsaData;
    int iResult;
    int i = 0;
    QString v4addr;
    struct hostent *remoteHost;
    struct in_addr addr;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        qDebug() << "WSA Start up failed";
    }

    remoteHost = gethostbyname("google.ru");

    if (remoteHost->h_addrtype == AF_INET)
    {
        while (remoteHost->h_addr_list[i] != 0)
        { //we take last ip addr in list
            addr.s_addr = *(u_long *) remoteHost->h_addr_list[i++];
            v4addr = inet_ntoa(addr);
            qDebug() << v4addr;
        }
    }
    return v4addr;
#endif

}

quint16 TSettings::GetServerPort() {
    return Settings->GetParameter("server.port");
}

bool TSettings::GetWindowFullscreen()
{
    return Settings->GetParameter("window.fullscreen");
}

void TSettings::SetWindowFullscreen(bool value)
{
    Settings->SetParameter("window.fullscreen", QString().number(value));
}

void TSettings::Load()
{
    try {
        Settings->Load(SETTINGS_FILENAME);
    } catch (const UException& ex) {
        qWarning() << ex.what();
    }
}

void TSettings::Save(bool keepOrigin)
{
    try {
        Settings->Save(SETTINGS_FILENAME, keepOrigin);
    } catch (const UException& ex) {
        qWarning() << ex.what();
    }
}
