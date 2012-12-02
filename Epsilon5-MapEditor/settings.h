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
    ~TSettings();
    QSize GetWindowSize() const;
    void SetWindowSize(const QSize& size);
    void Save();
    void Load();

private:
    USettings* mSettings;
};
//------------------------------------------------------------------------------
