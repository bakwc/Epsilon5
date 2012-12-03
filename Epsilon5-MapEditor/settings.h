// settings.h
#pragma once
#include <QObject>
#include <QSize>
#include <QPoint>
#include "../utils/usettings.h"
//------------------------------------------------------------------------------
class TSettings : public QObject {
    Q_OBJECT
public:
    explicit TSettings(QObject* parent = 0);
    ~TSettings();
    QSize GetWindowSize() const;
    void SetWindowSize(const QSize& size);
    QPoint GetWindowPos() const;
    void SetWindowPos(const QPoint& position);
    QString GetTexturesPath() const;
    void SetTexturesPath(const QString& path);
    QString GetMapsPath() const;
    void SetMapsPath(const QString& path);
    QString GetObjectsPath() const;
    void SetObjectsPath(const QString& path);
    void Save();
    void Load();

private:
    USettings* mSettings;
};
//------------------------------------------------------------------------------
