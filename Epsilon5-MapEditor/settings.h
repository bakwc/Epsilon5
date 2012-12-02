// settings.h
#pragma once
#include <QObject>
#include <QSize>
#include "../utils/usettings.h"
//------------------------------------------------------------------------------
class TSettings : public QObject {
    Q_OBJECT
public:
    explicit TSettings(QObject* parent = 0);
    QSize GetWindowSize() const;

private:
    USettings* mSettings;
};
//------------------------------------------------------------------------------
