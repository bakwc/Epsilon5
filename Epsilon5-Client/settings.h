#pragma once

#include <QObject>
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
