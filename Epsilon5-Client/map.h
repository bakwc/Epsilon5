#pragma once

#include <QObject>
#include <QImage>

class TMap : public QObject
{
    Q_OBJECT
public:
    TMap(const QString& fileName, QObject *parent = 0);
    QImage GetFrame(int x, int y);
private:
    size_t Width;
    size_t Height;
    QImage* Background;
};
