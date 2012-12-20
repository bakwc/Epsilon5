#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "settings.h"

#ifdef Q_OS_WIN32

#include <windows.h>
#include <winsock2.h>

#endif

#ifdef Q_OS_LINUX

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#endif


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

#ifdef Q_OS_LINUX
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];


    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // IPv4 OR IPv6
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(qPrintable(serverAddr), NULL, &hints, &res)) != 0) {
        qDebug() << serverAddr;
        qDebug() << "ERROR: getaddrinfo";
    }

    for(p = res;p != NULL; p = p->ai_next) {
        void *addr;


        // get pointer ipv4 or ipv6
        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        // convert ip to string
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        QString serverAddr = ipstr;
        qDebug() << serverAddr;
    }

    freeaddrinfo(res);

return serverAddr;
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
