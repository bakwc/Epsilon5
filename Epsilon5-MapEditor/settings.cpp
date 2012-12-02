// settings.cpp
#include <QDebug>
#include <QFile>
#include "../utils/uexception.h"
#include "settings.h"
//------------------------------------------------------------------------------
const quint32 DEFAULT_WINDOW_WIDTH = 800;
const quint32 DEFAULT_WINDOW_HEIGHT = 600;
const QString& SETTINGS_FILENAME = "settings.ini";
//------------------------------------------------------------------------------
TSettings::TSettings(QObject* parent)
    : QObject(parent)
    , mSettings(new USettings(this)) {
    // Defining default parameters
    USettings::TParametersHash parameters;
    parameters["window.width"] = QString().number(DEFAULT_WINDOW_WIDTH);
    parameters["window.height"] = QString().number(DEFAULT_WINDOW_HEIGHT);
    mSettings->LoadDefaults(parameters);
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
        mSettings->Save(SETTINGS_FILENAME, true);
    } catch (const UException& ex) {
        qWarning() << ex.what();
    }
}
//------------------------------------------------------------------------------
