// settings.cpp
#include "settings.h"
//------------------------------------------------------------------------------
const quint32 DEFAULT_WINDOW_WIDTH = 800;
const quint32 DEFAULT_WINDOW_HEIGHT = 600;
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
QSize TSettings::GetWindowSize() const
{
    return QSize(mSettings->GetParameter("window.width").toUInt(),
            mSettings->GetParameter("window.height").toUInt());
}
//------------------------------------------------------------------------------
