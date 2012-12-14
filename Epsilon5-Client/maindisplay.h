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
#include "menu.h"

class TApplication;

enum ETeam {
    T_One,
    T_Second,
    T_Neutral
};

struct TRespPoint {
    int X;
    int Y;
    ETeam Team;
};

struct TPlayerStat {
    size_t Id;
    size_t Score;
    size_t Deaths;
    size_t Kills;
};

class TMainDisplay : public QGLWidget, public utils::UFullscreenWrapper
{
    Q_OBJECT
public:
    explicit TMainDisplay(TApplication* application, QGLWidget* parent = 0);
    void Init();
    ~TMainDisplay();
    inline const Epsilon5::Control& GetControl() { return Control; }
    QPoint GetCenter();
    QPoint GetCursorPos();
public slots:
    void RedrawWorld();
    void toggleFullscreen();

private:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    QPoint GetPlayerCoordinatesAndPing();
    void DrawText(QPainter& painter, const QPoint& pos,
            const QString& text, int FONT_SIZE_PT);
    void DrawFps(QPainter& painter);
    void DrawPing(QPainter& painter);
    void DrawWorld(QPainter& painter);
    void DrawPlayers(QPainter& painter, QPainter& miniMap,
            const QPoint& playerPos, const QPoint& widgetCenter);
    void DrawBullets(QPainter& painter, const QPoint& playerPos,
            const QPoint& widgetCenter);
    void DrawObjects(QPainter& painter, QPainter& miniMap,
            const QPoint& playerPos, const QPoint& widgetCenter);
    void DrawRespPoints(QPainter& painter, QPainter& miniMap,
            const QPoint& playerPos, const QPoint& widgetCenter);
    void DrawStats(QPainter& painter);

    void SetMovementKeysState(bool state, const QKeyEvent* event);

private:
    TApplication* Application;
    TImageStorage* Images;
    QQueue<Epsilon5::World> PacketsQueue;
    Epsilon5::Control Control;
    TMap* Map;
    TObjects* Objects;
    const Epsilon5::World* CurrentWorld;
    QHash<size_t, QString> PlayerNames;
    QVector<TRespPoint> RespPoints;
    QVector<TPlayerStat> Stats;
    bool ShowStats;
    int Ping;
    TMenu Menu;
};
