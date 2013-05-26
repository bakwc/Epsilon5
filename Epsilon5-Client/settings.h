#pragma once

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "../utils/usettings.h"

class TSettings: public QObject {
    Q_OBJECT
public:
    explicit TSettings(QObject* parent);
    ~TSettings();

    QString GetNickname();
    QString GetServerAddr();
    quint16 GetServerPort();
    bool GetWindowFullscreen();

    void SetWindowFullscreen(bool value = true);

    void Save(bool keepOrigin = true);
    void Load();

private:
    USettings* Settings;
};
