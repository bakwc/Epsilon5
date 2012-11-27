#pragma once

#include <QObject>
#include <QPoint>
#include <QHash>

class TObjects : public QObject
{
    Q_OBJECT
public:
    explicit TObjects(QObject *parent = 0);
    void LoadObjects(const QString& fileName);
    QPoint GetObjectSize(size_t id);
    bool IsDynamicObject(size_t id);
private:
    QHash<size_t, QPoint> Objects;
    QHash<size_t, bool> ObjectsIsDyn;
};
