#include <QDebug>
#include "../utils/uexception.h"
#include "settings.h"

const char* DEFAULT_SERVER_ADDRESS = "0.0.0.0";
const quint16 DEFAULT_SERVER_PORT = 14567;
const quint8 DEFAULT_GAMEPLAY_FRIENDLYFIRE = 50;
const char* SETTINGS_FILENAME = "settings.ini";

TSettings::TSettings(QObject* parent)
    : QObject(parent)
    , Settings(new USettings(this))
{
    // Define default params
    USettings::TParametersHash params;
    params["server.address"] = QString(DEFAULT_SERVER_ADDRESS);
    params["server.port"] = QString().number(DEFAULT_SERVER_PORT);
    params["gameplay.friendlyfire"] = QString().number(DEFAULT_GAMEPLAY_FRIENDLYFIRE);
    Settings->DefineParams(params);
    Load();
}

QString TSettings::GetServerAddress()
{
    return Settings->GetParameter("server.address");
}

quint16 TSettings::GetServerPort()
{
    return Settings->GetParameter("server.port");
}

quint8 TSettings::GetGameplayFriendlyFire()
{
    return Settings->GetParameter("gameplay.friendlyfire");
}

void TSettings::Load()
{
    try {
        Settings->Load(SETTINGS_FILENAME);
    } catch (const UException& ex) {
        qWarning() << Q_FUNC_INFO << ex.what() << "(Default values used)";
    }
}
