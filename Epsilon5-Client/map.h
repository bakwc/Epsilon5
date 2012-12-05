#pragma once

#include <QObject>
#include <QImage>
#include <QPainter>

class TMap : public QObject
{
    Q_OBJECT
public:
    TMap(QObject *parent = 0);
    ~TMap();
    void DrawFrame(int x, int y, const QSize& frameSize, QPainter &painter);
    QPixmap GetBackground() { return QPixmap::fromImage(*Background); }
public slots:
    void LoadMap(QString map);
private:
    size_t Width;
    size_t Height;
    QImage* Background;
    bool Loaded;
};
