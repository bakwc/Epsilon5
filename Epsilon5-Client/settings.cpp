#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "settings.h"

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
    return Settings->GetParameter("server.address");
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
