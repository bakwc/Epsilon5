#pragma once

#include <QObject>
#include <QPointF>
#include <QHash>

class TObjects : public QObject
{
    Q_OBJECT
public:
    explicit TObjects(QObject *parent = 0);
    void LoadObjects(const QString& fileName);
    QPointF GetObjectSize(size_t id);
private:
    QHash<size_t, QPointF> Objects;
};
