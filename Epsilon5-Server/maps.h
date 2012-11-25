#pragma once

#include <QObject>
#include <QString>
#include <QStringList>

class TMaps : public QObject
{
    Q_OBJECT
public:
    explicit TMaps(QObject *parent = 0);
    void LoadMaplist(const QString& filename);
    void LoadNextMap();
    QString GetCurrentMap();
signals:
    void SpawnObject(size_t id, double x, double y);
private:
    void LoadMap(const QString& filename);
private:
    QStringList MapFiles;
    size_t currentMap;
};
