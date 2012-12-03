// settings.cpp
#include <QDebug>
#include <QFile>
#include "../utils/uexception.h"
#include "settings.h"
//------------------------------------------------------------------------------
const quint32 DEFAULT_WINDOW_WIDTH = 800;
const quint32 DEFAULT_WINDOW_HEIGHT = 600;
const qint32 DEFAULT_WINDOW_POSX = 100;
const qint32 DEFAULT_WINDOW_POSY = 50;
const char* SETTINGS_FILENAME = "settings.ini";
//------------------------------------------------------------------------------
TSettings::TSettings(QObject* parent)
    : QObject(parent)
    , mSettings(new USettings(this)) {
    // Defining default parameters
    USettings::TParametersHash parameters;
    parameters["window.width"] = QString().number(DEFAULT_WINDOW_WIDTH);
    parameters["window.height"] = QString().number(DEFAULT_WINDOW_HEIGHT);
    parameters["window.posx"] = QString().number(DEFAULT_WINDOW_POSX);
    parameters["window.posy"] = QString().number(DEFAULT_WINDOW_POSY);
    parameters["data.path"] = "";
    parameters["maps.path"] = "";
    parameters["objects.path"] = "";
    mSettings->LoadDefaults(parameters);
    Load();
}
//------------------------------------------------------------------------------
TSettings::~TSettings() {
    Save();
}
//------------------------------------------------------------------------------
QSize TSettings::GetWindowSize() const {
    return QSize(mSettings->GetParameter("window.width"),
                 mSettings->GetParameter("window.height"));
}
//------------------------------------------------------------------------------
void TSettings::SetWindowSize(const QSize& size) {
    mSettings->SetParameter("window.width", QString().number(size.width()));
    mSettings->SetParameter("window.height", QString().number(size.height()));
}
//------------------------------------------------------------------------------
QPoint TSettings::GetWindowPos() const {
    return QPoint(mSettings->GetParameter("window.posx"),
                  mSettings->GetParameter("window.posy"));
}
//------------------------------------------------------------------------------
void TSettings::SetWindowPos(const QPoint& position) {
    mSettings->SetParameter("window.posx", QString().number(position.x()));
    mSettings->SetParameter("window.posy", QString().number(position.y()));
}
//------------------------------------------------------------------------------
QString TSettings::GetDataPath() const {
    return mSettings->GetParameter("data.path");
}
//------------------------------------------------------------------------------
void TSettings::SetDataPath(const QString& path) {
    mSettings->SetParameter("data.path", path);
}
//------------------------------------------------------------------------------
QString TSettings::GetMapsPath() const {
    return mSettings->GetParameter("maps.path");
}
//------------------------------------------------------------------------------
void TSettings::SetMapsPath(const QString& path) {
    mSettings->SetParameter("maps.path", path);
}
//------------------------------------------------------------------------------
QString TSettings::GetObjectsPath() const {
    return mSettings->GetParameter("objects.path");
}
//------------------------------------------------------------------------------
void TSettings::SetObjectsPath(const QString& path) {
    mSettings->SetParameter("objects.path", path);
}
//------------------------------------------------------------------------------
void TSettings::Load() {
    try {
        mSettings->Load(SETTINGS_FILENAME);
    } catch (const UException& ex) {
        qWarning() << ex.what();
    }
}
//------------------------------------------------------------------------------
void TSettings::Save() {
    try {
        mSettings->Save(SETTINGS_FILENAME, false);
    } catch (const UException& ex) {
        qWarning() << ex.what();
    }
}
//------------------------------------------------------------------------------
