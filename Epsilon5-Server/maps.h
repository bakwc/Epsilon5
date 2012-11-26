#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QPoint>

class TMaps : public QObject
{
    Q_OBJECT
public:
    explicit TMaps(QObject *parent = 0);
    void LoadMaplist(const QString& fileName);
    void LoadFirstMap();
    void LoadNextMap();
    QString GetCurrentMap();
    QPoint GetMapSize();
signals:
    void SpawnObject(size_t id, int x, int y, double angle);
    void ClearObjects();
private:
    void LoadConfig(const QString& fileName);
    void LoadObjects(const QString& fileName);
private:
    QStringList MapFiles;
    int CurrentMap;
    QPoint MapSize;
};
