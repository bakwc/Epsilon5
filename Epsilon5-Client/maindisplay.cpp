#include <qmath.h>
#include <QTime>
#include <QDesktopWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QPixmap>
#include <QMatrix>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "../utils/uexception.h"
#include "network.h"
#include "maindisplay.h"
#include "application.h"

const quint16 BASE_WINDOW_WIDTH = 800;
const quint16 BASE_WINDOW_HEIGHT = 600;

int GetCorrect(int player, int enemy) {
    return enemy - player;
}

static double getAngle(const QPoint& point)
{
    double angle;
    double x=point.x();
    double y=point.y();
    if (x>0) angle = atan(y/x); else
    if (x<0 && y>0) angle = M_PI + atan(y/x); else
    if (x<0 && y<0) angle = -M_PI + atan(y/x); else
    if (x==0 && y>0) angle = M_PI/2; else
    angle = -M_PI/2;
    return -angle;
}

TMainDisplay::TMainDisplay(TApplication *application, QGLWidget *parent)
    : QGLWidget(parent)
    , UFullscreenWrapper(this)
    , Application(application)
    , Images(new TImageStorage(this))
    , Map(new TMap(this))
    , Objects(new TObjects(this))
    , IsFullScreenWindowed(false)
    , CurrentWorld(NULL)
{
    setBaseSize(BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT);
    setFixedSize(baseSize());

    Control.set_angle(0);
    Control.mutable_keystatus()->set_keyattack1(false);
    Control.mutable_keystatus()->set_keyattack2(false);
    Control.mutable_keystatus()->set_keyleft(false);
    Control.mutable_keystatus()->set_keyright(false);
    Control.mutable_keystatus()->set_keyup(false);
    Control.mutable_keystatus()->set_keydown(false);

    startTimer(20);
}

void TMainDisplay::Init() {
    Images->LoadAll();
    Objects->LoadObjects("objects/objects.txt");

    connect(Application->GetNetwork(), SIGNAL(LoadMap(QString)),
            Map, SLOT(LoadMap(QString)));
}

TMainDisplay::~TMainDisplay()
{
    CurrentWorld = NULL;

    if (isFullScreen() && !IsFullScreenWindowed)
        restoreMode();
}

void TMainDisplay::RedrawWorld() {
    CurrentWorld = &((TNetwork*)(QObject::sender()))->GetWorld();
}

void TMainDisplay::timerEvent(QTimerEvent *) {
    this->update();
}

void TMainDisplay::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    drawWorld(painter);
    drawFps(painter);
    drawPing(painter);

}

void TMainDisplay::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        Control.mutable_keystatus()->set_keyattack1(true);
    } else {
        Control.mutable_keystatus()->set_keyattack2(true);
    }
}

void TMainDisplay::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        Control.mutable_keystatus()->set_keyattack1(false);
    } else {
        Control.mutable_keystatus()->set_keyattack2(false);
    }
}

void TMainDisplay::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        Control.mutable_keystatus()->set_keyup(true);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        Control.mutable_keystatus()->set_keydown(true);
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        Control.mutable_keystatus()->set_keyright(true);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        Control.mutable_keystatus()->set_keyleft(true);
        break;
    default:
        break;
    }
}

void TMainDisplay::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        Control.mutable_keystatus()->set_keyup(false);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        Control.mutable_keystatus()->set_keydown(false);
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        Control.mutable_keystatus()->set_keyright(false);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        Control.mutable_keystatus()->set_keyleft(false);
        break;
    case Qt::Key_F11:
        if(event->modifiers().testFlag(Qt::ShiftModifier)) {
            toggleFullscreen();
        }
        else {
            toggleFullscreenWindowed();
        }
        break;
    case Qt::Key_F12:
        close();
        break;
    default:
        break;
    }
}

void TMainDisplay::toggleFullscreenWindowed() {
    if( isFullScreen() && !IsFullScreenWindowed )
        restoreMode();

    setWindowState( windowState() ^ Qt::WindowFullScreen );
    IsFullScreenWindowed = isFullScreen();
    if( isFullScreen() )
    {
        QDesktopWidget dw;
        const QRect& screenRect = dw.screenGeometry(dw.screenNumber(this));
        setFixedSize(screenRect.size());
        return;
    }
    setFixedSize(baseSize());
}

void TMainDisplay::toggleFullscreen() {
    if( isFullScreen() && !IsFullScreenWindowed )
    {
        restoreMode();
        return;
    }
    changeToMode(BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT);
    IsFullScreenWindowed = false;
}

void TMainDisplay::drawFps(QPainter& painter)
{
    // TODO: move fps calculation to another place, here must be only drawing
    static int frames = 0;
    static int fps = 0;
    static QTime lasttime = QTime::currentTime();

    const QTime& time = QTime::currentTime();
    if( lasttime.msecsTo(time) >= 1000 )
    {
        fps = frames;
        frames = 0;
        lasttime = time;
    }

    const QPen penOld = painter.pen();
    drawText(painter, QPoint(0, 10), QString("Fps: %1").arg(fps));

    ++frames;
}

void TMainDisplay::drawPing(QPainter& painter)
{
    qint64 Ping = Application->GetNetwork()->GetPing();
    drawText(painter, QPoint(0, 24), QString("Ping: %1").arg(Ping));
}

void TMainDisplay::drawText(QPainter &painter, const QPoint& pos, const QString& text)
{
    const int FONT_SIZE_PT = 10;
    // Helvetica font present on all Systems
    painter.setFont(QFont("Helvetica", FONT_SIZE_PT));
    painter.setPen(Qt::black);
    painter.drawText(pos.x() + 1, pos.y() + 1, text);
    painter.setPen(Qt::darkGray);
    painter.drawText(pos.x(), pos.y(), text);
}

void TMainDisplay::drawWorld(QPainter &painter)
{
    if( !CurrentWorld )
        return;

    try {
        QPoint gamerPos, cursorPos;

        const int nickMaxWidth = 200;
        int playerX = 0;
        int playerY = 0;
        bool playerFound = false;

        size_t playerId = Application->GetNetwork()->GetId();

        for (int i = 0; i != CurrentWorld->players_size(); i++) {
            const Epsilon5::Player &player = CurrentWorld->players(i);
            if ((size_t)player.id() == playerId) {
                playerX = player.x();
                playerY = player.y();
                playerFound = true;
            }
        }


        QPoint widgetCenter(width() / 2, height() / 2);
        Map->DrawFrame(playerX, playerY, size(), painter);

        const QFont oldFont = painter.font();
        const QPen oldPen = painter.pen();
        QFont nickFont(oldFont);
        nickFont.setBold(true);
        nickFont.setPointSize(12);

        QImage miniMapImg(100, 100, QImage::Format_ARGB32);
        miniMapImg.fill(qRgba(255, 255, 255, 100));
        QPainter miniMap(&miniMapImg);

        // Players drawing
        const QImage* img;
        for (int i = 0; i != CurrentWorld->players_size(); i++) {
            const Epsilon5::Player &player = CurrentWorld->players(i);

            int cx = GetCorrect(playerX, player.x());
            int cy = GetCorrect(playerY, player.y());

            QString nickName;
            if (player.has_name()) {
                nickName = player.name().c_str();
                PlayerNames[player.id()] = nickName;
            } else {
                if (PlayerNames.find(player.id()) != PlayerNames.end()) {
                    nickName = PlayerNames[player.id()];
                }
            }

            size_t hp = player.hp();

            if ((size_t)player.id() == Application->GetNetwork()->GetId()) {
                gamerPos.setX(widgetCenter.x() + cx);
                gamerPos.setY(widgetCenter.y() + cy);
                img = &Images->GetImage("player");
                miniMap.setPen(Qt::red);
                nickName += " - " + QString::number(hp) + "%";
            } else {
                img = &Images->GetImage("enemy");
                miniMap.setPen(Qt::black);
            }

            miniMap.drawEllipse(50 + player.x() / 40, 50 + player.y() / 40, 2, 2);

            painter.drawImage(widgetCenter.x() + cx - img->width() / 2,
                              widgetCenter.y() + cy - img->height() / 2, *img);

            painter.setPen(Qt::yellow);
            painter.setFont(nickFont);
            QRect nickRect = QRect(widgetCenter.x() + cx - nickMaxWidth/2,
                            widgetCenter.y() + cy - img->height()/2
                                   - painter.fontInfo().pixelSize(),
                            nickMaxWidth, painter.fontInfo().pixelSize());

            painter.drawText(nickRect, Qt::AlignTop | Qt::AlignHCenter, nickName);
            painter.setPen(oldPen);
            painter.setFont(oldFont);
        }

        // Bullets drawing
        img = &Images->GetImage("bullet");

        for (int i = 0; i != CurrentWorld->bullets_size(); i++) {
            const Epsilon5::Bullet &bullet = CurrentWorld->bullets(i);
            int cx = GetCorrect(playerX, bullet.x());
            int cy = GetCorrect(playerY, bullet.y());

            painter.drawImage(widgetCenter.x() + cx - img->width() / 2,
                              widgetCenter.y() + cy - img->height() / 2, *img);
        }

        // Objects drawing
        for (int i = 0; i != CurrentWorld->objects_size(); i++) {
            const Epsilon5::Object& object = CurrentWorld->objects(i);

            // BUG: Type of ID mismatch (int32 vs size_t on server)
            if( object.id() < 0 )
                continue;

            int cx = GetCorrect(playerX, object.x());
            int cy = GetCorrect(playerY, object.y());

            img = Objects->GetImageById(object.id());
            QTransform transform;
            transform.rotate(object.angle() * 180 / M_PI);
            QImage rimg = img->transformed(transform);

            painter.drawImage(widgetCenter.x() + cx - rimg.width() / 2,
                              widgetCenter.y() + cy - rimg.height() / 2, rimg);
            painter.drawEllipse(widgetCenter.x() + cx, widgetCenter.y() + cy, 2, 2);
        }

        // Minimap drawing
        painter.drawImage(10, 30, miniMapImg);

        cursorPos = this->mapFromGlobal(QCursor::pos());
        double angle = getAngle(cursorPos - gamerPos);
        Control.set_angle(angle);

        this->update();
    } catch (const std::exception& e) {
        qDebug() << Q_FUNC_INFO << ": " << e.what();
    }
}
