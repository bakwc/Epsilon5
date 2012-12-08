#pragma once
#include <QGLWidget>
#include <QImage>
#include <QQueue>
#include <QHash>
#include <QVector>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "imagestorage.h"
#include "map.h"
#include "objects.h"
#include "../utils/ufullscreenwrapper.h"

class TApplication;

enum ETeam {
    T_One,
    T_Second,
    T_Neutral
};

struct RespPoint {
    int X;
    int Y;
    ETeam Team;
};

class TMainDisplay : public QGLWidget, public utils::UFullscreenWrapper
{
    Q_OBJECT
public:
    explicit TMainDisplay(TApplication* application, QGLWidget *parent = 0);
    void Init();
    ~TMainDisplay();
    inline const Epsilon5::Control& GetControl() { return Control; }

public slots:
    void RedrawWorld();
    void toggleFullscreen();
    void toggleFullscreenWindowed();

private:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    QPoint GetPlayerCoordinates();
    void DrawText(QPainter& painter, const QPoint& pos, const QString& text, int FONT_SIZE_PT);
    void DrawFps(QPainter& painter);
    void DrawPing(QPainter& painter);
    void DrawWorld(QPainter& painter);
    void DrawPlayers(QPainter& painter, QPainter& miniMap, const QPoint& playerPos, const QPoint& widgetCenter);
    void DrawBullets(QPainter& painter, const QPoint& playerPos, const QPoint& widgetCenter);
    void DrawObjects(QPainter& painter, const QPoint& playerPos, const QPoint& widgetCenter);
    void DrawRespPoints(QPainter& painter, const QPoint& playerPos, const QPoint& widgetCenter);

    void SetMovementKeysState(bool state, const QKeyEvent* event);

private:
    TApplication* Application;
    TImageStorage* Images;
    QQueue<Epsilon5::World> PacketsQueue;
    Epsilon5::Control Control;
    TMap* Map;
    TObjects* Objects;
    bool IsFullScreenWindowed;
    const Epsilon5::World* CurrentWorld;
    QHash<size_t, QString> PlayerNames;
    QVector<RespPoint> RespPoints;
    int Ping;
};
