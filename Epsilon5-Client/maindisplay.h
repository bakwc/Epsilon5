#pragma once
#include <QGLWidget>
#include <QImage>
#include <QQueue>
#include <QHash>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "imagestorage.h"
#include "map.h"
#include "objects.h"
#include "../utils/ufullscreenwrapper.h"

class TApplication;

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
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void drawFps(QPainter& painter);
    void drawPing(QPainter& painter);
    void drawWorld(QPainter& painter);

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
};
