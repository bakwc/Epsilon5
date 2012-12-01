#pragma once
#include <QGLWidget>
#include <QImage>
#include <QQueue>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "imagestorage.h"
#include "map.h"
#include "objects.h"

class TApplication;

class TMainDisplay : public QGLWidget
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

private:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void drawFps(QPainter& painter);
    void drawWorld(QPainter& painter);

private:
    TApplication* Application;
    TImageStorage* Images;
    QQueue<Epsilon5::World> PacketsQueue;
    Epsilon5::Control Control;
    TMap* Map;
    TObjects* Objects;
    const Epsilon5::World* CurrentWorld;
};
