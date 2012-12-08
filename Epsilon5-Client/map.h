#pragma once

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QPoint>

class TMap : public QObject
{
    Q_OBJECT
public:
    TMap(QObject *parent = 0);
    ~TMap();

    // Draw background at correct position
    void DrawBackground(const QPoint& playerPos, const QSize& frameSize, QPainter &painter);
public slots:
    void LoadMap(QString map);
private:
    size_t Width;
    size_t Height;
    QImage* Background;
    bool Loaded;
};
