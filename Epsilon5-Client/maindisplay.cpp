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

TMainDisplay::TMainDisplay(TApplication *application, QWidget *parent)
    : QWidget(parent)
    , Application(application)
    , Frame(new QImage(1680, 1050, QImage::Format_ARGB32))
    , Images(new TImageStorage(this))
    , Map(new TMap(this))
    , Objects(new TObjects(this))
{
    setBaseSize(800, 600);
    setFixedSize(baseSize());

    Control.set_angle(0);
    Control.mutable_keystatus()->set_keyattack1(false);
    Control.mutable_keystatus()->set_keyattack2(false);
    Control.mutable_keystatus()->set_keyleft(false);
    Control.mutable_keystatus()->set_keyright(false);
    Control.mutable_keystatus()->set_keyup(false);
    Control.mutable_keystatus()->set_keydown(false);
}

void TMainDisplay::Init() {
    Images->LoadAll();
    Objects->LoadObjects("objects/objects.txt");

    connect(Application->GetNetwork(), SIGNAL(LoadMap(QString)),
            Map, SLOT(LoadMap(QString)));
}

TMainDisplay::~TMainDisplay()
{
    if (Frame) {
        delete Frame;
    }
}

void TMainDisplay::RedrawWorld() {
    try {
        Epsilon5::World world = ((TNetwork*)(QObject::sender()))->GetWorld();
        Frame->fill(Qt::black);
        QPainter painter(Frame);
        QPoint gamerPos, cursorPos;

        const int nickMaxWidth = 200;
        int playerX = 0;
        int playerY = 0;
        bool playerFound = false;

        size_t playerId = Application->GetNetwork()->GetId();

        for (int i = 0; i != world.players_size(); i++) {
            const Epsilon5::Player &player = world.players(i);
            if ((size_t)player.id() == playerId) {
                playerX = player.x();
                playerY = player.y();
                playerFound = true;
            }
        }

        if (!playerFound) {
            throw UException("No player found with id " + QString::number(playerId));
        }

        QPoint widgetCenter(width() / 2, height() / 2);
        QImage background = Map->GetFrame(playerX, playerY, size());
        painter.drawImage(0, 0, background);

        const QFont oldFont = painter.font();
        const QPen oldPen = painter.pen();
        QFont nickFont(oldFont);
        nickFont.setBold(true);
        nickFont.setPointSize(12);

        const QImage* img;
        for (int i = 0; i != world.players_size(); i++) {
            const Epsilon5::Player &player = world.players(i);

            int cx = GetCorrect(playerX, player.x());
            int cy = GetCorrect(playerY, player.y());
            QString nickName = player.name().c_str();
            if ((size_t)player.id() == Application->GetNetwork()->GetId()) {
                gamerPos.setX(widgetCenter.x() + cx);
                gamerPos.setY(widgetCenter.y() + cy);
                img = &Images->GetImage("player");
            } else {
                img = &Images->GetImage("enemy");
            }
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

        img = &Images->GetImage("bullet");

        for (int i = 0; i != world.bullets_size(); i++) {
            const Epsilon5::Bullet &bullet = world.bullets(i);
            int cx = GetCorrect(playerX, bullet.x());
            int cy = GetCorrect(playerY, bullet.y());

            painter.drawImage(widgetCenter.x() + cx - img->width() / 2,
                              widgetCenter.y() + cy - img->height() / 2, *img);
        }

        for (int i = 0; i != world.objects_size(); i++) {
            const Epsilon5::Object& object = world.objects(i);
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

        cursorPos = this->mapFromGlobal(QCursor::pos());
        double angle = getAngle(cursorPos - gamerPos);
        Control.set_angle(angle);

        this->update();
    } catch (const std::exception& e) {
        qDebug() << Q_FUNC_INFO << ": " << e.what();
    }
}

void TMainDisplay::timerEvent(QTimerEvent *) {

}

void TMainDisplay::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, *Frame);
    drawFps(painter);
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
        Control.mutable_keystatus()->set_keyup(true);
        break;
    case Qt::Key_Down:
        Control.mutable_keystatus()->set_keydown(true);
        break;
    case Qt::Key_Right:
        Control.mutable_keystatus()->set_keyright(true);
        break;
    case Qt::Key_Left:
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
        Control.mutable_keystatus()->set_keyup(false);
        break;
    case Qt::Key_Down:
        Control.mutable_keystatus()->set_keydown(false);
        break;
    case Qt::Key_Right:
        Control.mutable_keystatus()->set_keyright(false);
        break;
    case Qt::Key_Left:
        Control.mutable_keystatus()->set_keyleft(false);
        break;
    case Qt::Key_F11:
        toggleFullscreen();
        break;
    case Qt::Key_F12:
        close();
        break;
    default:
        break;
    }
}

void TMainDisplay::toggleFullscreen()
{
    setWindowState( windowState() ^ Qt::WindowFullScreen );
    if( isFullScreen() )
    {
        QDesktopWidget dw;
        const QRect& screenRect = dw.screenGeometry(dw.screenNumber(this));
        setFixedSize(screenRect.size());
        return;
    }
    setFixedSize(baseSize());
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
    const QString& fpsString = QString("FPS: %1").arg(fps);
    painter.setPen(Qt::black);
    painter.drawText(1, 11, fpsString);
    painter.setPen(Qt::darkGray);
    painter.drawText(0, 10, fpsString);
    painter.setPen(penOld);

    ++frames;
}
