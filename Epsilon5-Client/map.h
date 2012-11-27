#pragma once

#include <QObject>
#include <QImage>

class TMap : public QObject
{
    Q_OBJECT
public:
    TMap(QObject *parent = 0);
    ~TMap();
    QImage GetFrame(int x, int y);
public slots:
    void LoadMap(QString map);
private:
    size_t Width;
    size_t Height;
    QImage* Background;
    bool Loaded;
};
