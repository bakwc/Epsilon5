#include <qmath.h>
#include <QPainter>
#include <QKeyEvent>
#include "../Epslion5-Proto/Epsilon5.pb.h"
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
    , Frame(new QImage(800, 600, QImage::Format_ARGB32))
    , Images(new TImageStorage(this))
    , Map(new TMap(this))
{
    Images->LoadAll();
    setFixedSize(800, 600);
    Control.set_angle(0);
    Control.mutable_keystatus()->set_keyattack1(false);
    Control.mutable_keystatus()->set_keyattack2(false);
    Control.mutable_keystatus()->set_keyleft(false);
    Control.mutable_keystatus()->set_keyright(false);
    Control.mutable_keystatus()->set_keyup(false);
    Control.mutable_keystatus()->set_keydown(false);
    //Started = false;
    //startTimer(10);
}

void TMainDisplay::Init() {
    connect(Application->GetNetwork(), SIGNAL(LoadMap(QString)),
            Map, SLOT(LoadMap(QString)));
}

TMainDisplay::~TMainDisplay()
{
    if( Frame )
        delete Frame;
}

void TMainDisplay::RedrawWorld() {
    Epsilon5::World world = ((TNetwork*)(QObject::sender()))->GetWorld();
    Frame->fill(Qt::black);
    QPainter painter(Frame);

    QPoint gamerPos, cursorPos;

    int playerX = 0;
    int playerY = 0;

    for (int i = 0; i != world.players_size(); i++) {
        const Epsilon5::Player &player = world.players(i);
        if (player.id() == Application->GetNetwork()->GetId()) {
            playerX = player.x();
            playerY = player.y();
        }
    }
    QImage background = Map->GetFrame(playerX, playerY);
    painter.drawImage(0, 0, background);

    const QImage* img;
    for (int i = 0; i != world.players_size(); i++) {
        const Epsilon5::Player &player = world.players(i);

        int cx = GetCorrect(playerX, player.x());
        int cy = GetCorrect(playerY, player.y());
        QString nickName = player.name().c_str();
        if (player.id() == Application->GetNetwork()->GetId()) {
            gamerPos.setX(400 + cx);
            gamerPos.setY(300 + cy);
            img = &Images->GetImage("player");
        } else {
            img = &Images->GetImage("enemy");
        }
        painter.drawImage(400 + cx - img->width() / 2, 300 + cy - img->height() / 2, *img);
        painter.setPen(Qt::yellow);
        painter.drawText(400 + cx - 5, 300 + cy - 18, nickName);
    }

    img = &Images->GetImage("bullet");
    //qDebug() << "bullets: " << world.bullets_size();
    for (int i = 0; i != world.bullets_size(); i++) {
        const Epsilon5::Bullet &bullet = world.bullets(i);
        int cx = GetCorrect(playerX, bullet.x());
        int cy = GetCorrect(playerY, bullet.y());;
        painter.drawImage(400 + cx - img->width() / 2, 300 + cy - img->height() / 2, *img);
    }

    cursorPos = this->mapFromGlobal(QCursor::pos());
    double angle = getAngle(cursorPos - gamerPos);
    Control.set_angle(angle);

    this->update();
}

void TMainDisplay::timerEvent(QTimerEvent *) {

}

void TMainDisplay::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, *Frame);
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
    default:
        break;
    }
}

