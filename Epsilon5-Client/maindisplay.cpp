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


#ifdef Q_OS_UNIX
#include <linux/input.h>
#endif

const quint16 BASE_WINDOW_WIDTH = 800;
const quint16 BASE_WINDOW_HEIGHT = 600;
const quint8 MAX_MINIMAP_SIZE = 200;    // max points of width or height

QPoint GetCorrect(QPoint playerPos, QPoint objectPos) {
    return objectPos - playerPos;
}

// Transform direction vector into angle
static double getAngle(const QPoint& point)
{
    double angle;
    double x = point.x();
    double y = point.y();
    if (x > 0) {
        angle = atan(y / x);
    } else if (x < 0 && y > 0) {
        angle = M_PI + atan(y / x);
    } else if (x < 0 && y < 0) {
        angle = -M_PI + atan(y / x);
    } else if (x == 0 && y > 0) {
        angle = M_PI / 2;
    } else {
        angle = -M_PI / 2;
    }
    return -angle;
}

TMainDisplay::TMainDisplay(TApplication* application, QGLWidget* parent)
    : QGLWidget(parent)
    , UFullscreenWrapper(this)
    , Application(application)
    , Images(new TImageStorage(this))
    , Map(new TMap(this))
    , Objects(new TObjects(this))
    , CurrentWorld(NULL)
    , ShowStats(false)
    , Menu(Images)
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
    Control.set_weapon(Epsilon5::Pistol);

    startTimer(20);
}

void TMainDisplay::Init() {
    Images->LoadAll();
    Objects->LoadObjects("objects/objects.txt");

    connect(Application->GetNetwork(), SIGNAL(LoadMap(QString)),
            Map, SLOT(LoadMap(QString)));

    Menu.Init();
}

TMainDisplay::~TMainDisplay() {
    CurrentWorld = NULL;
    Application->GetSettings()->SetWindowFullscreen(isFullScreen());
}

void TMainDisplay::RedrawWorld() {
    CurrentWorld = &((TNetwork*)(QObject::sender()))->GetWorld();
}

void TMainDisplay::timerEvent(QTimerEvent*) {
    this->update();
}

void TMainDisplay::paintEvent(QPaintEvent*) {
    EState state = Application->GetState();
    QPainter painter(this);
    switch (state) {
    case ST_Connecting : {
        painter.fillRect(0, 0, width(), height(), Qt::black);
    } break;
    case ST_LoadingMap: {
        painter.fillRect(0, 0, width(), height(), Qt::black);
    } break;
    case ST_MainMenu : {
        Menu.paint(&painter);
    } break;
    default:
        DrawWorld(painter);
        DrawFps(painter);
        DrawPing(painter);

        if( !Application->GetNetwork()->IsServerAlive() )
            DrawText(painter, QPoint(width() / 2 - 50, height() / 2 - 5), tr("Connection lost..."), 28);
        break;
    }
}

void TMainDisplay::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        Control.mutable_keystatus()->set_keyattack1(true);
    } else {
        Control.mutable_keystatus()->set_keyattack2(true);
    }
    qApp->sendEvent(&Menu, event);
}

void TMainDisplay::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        Control.mutable_keystatus()->set_keyattack1(false);
    } else {
        Control.mutable_keystatus()->set_keyattack2(false);
    }
}

void TMainDisplay::SetMovementKeysState(bool state, const QKeyEvent *event)
{
#ifdef Q_OS_UNIX
    // TEST: Codes in input.h differ from event->scancodes by MAGIC_NUMBER.
    // Need some checks
    const int MAGIC_NUMBER = 8;
    if( event->nativeScanCode() == (KEY_W + MAGIC_NUMBER))
        Control.mutable_keystatus()->set_keyup(state);
    if( event->nativeScanCode() == (KEY_S + MAGIC_NUMBER))
        Control.mutable_keystatus()->set_keydown(state);
    if( event->nativeScanCode() == (KEY_A + MAGIC_NUMBER))
        Control.mutable_keystatus()->set_keyleft(state);
    if( event->nativeScanCode() == (KEY_D + MAGIC_NUMBER))
        Control.mutable_keystatus()->set_keyright(state);
#endif
#ifdef Q_OS_WIN
    if( event->key() == Qt::Key_W || event->nativeVirtualKey() == Qt::Key_W )
        Control.mutable_keystatus()->set_keyup(state);
    if( event->key() == Qt::Key_S || event->nativeVirtualKey() == Qt::Key_S )
        Control.mutable_keystatus()->set_keydown(state);
    if( event->key() == Qt::Key_A || event->nativeVirtualKey() == Qt::Key_A )
        Control.mutable_keystatus()->set_keyleft(state);
    if( event->key() == Qt::Key_D || event->nativeVirtualKey() == Qt::Key_D )
        Control.mutable_keystatus()->set_keyright(state);
#endif
    if( event->key() == Qt::Key_Up )
        Control.mutable_keystatus()->set_keyup(state);
    if( event->key() == Qt::Key_Down )
        Control.mutable_keystatus()->set_keydown(state);
    if( event->key() == Qt::Key_Left )
        Control.mutable_keystatus()->set_keyleft(state);
    if( event->key() == Qt::Key_Right )
        Control.mutable_keystatus()->set_keyright(state);
}

void TMainDisplay::keyPressEvent(QKeyEvent *event)
{
    SetMovementKeysState(true, event);

    switch(event->key()) {
    case '1':
        Control.set_weapon(Epsilon5::Pistol);
        break;
    case '2':
        Control.set_weapon(Epsilon5::Machinegun);
        break;
    case '3':
        Control.set_weapon(Epsilon5::Shotgun);
        break;
    case Qt::Key_Tab:
        ShowStats = true;
        break;
    default:
        break;
    }
}

void TMainDisplay::keyReleaseEvent(QKeyEvent* event)
{
    SetMovementKeysState(false, event);

    switch (event->key()) {
    case Qt::Key_F11:
        toggleFullscreen();
        break;
#ifdef QT_DEBUG
    case Qt::Key_F12:
        Application->GetNetwork()->Stop();
        close();
#endif
    case Qt::Key_Escape:
        Application->GetNetwork()->Stop();
        break;
    case Qt::Key_Tab:
        ShowStats = false;
        break;
    default:
        break;
    }
}

void TMainDisplay::toggleFullscreen() {
    if (isFullScreen()) {
        this->showNormal();
        setFixedSize(BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT);
    } else {
        QDesktopWidget dw;
        const QRect& screenRect = dw.screenGeometry(dw.screenNumber(this));
        setFixedSize(screenRect.size());
        this->showFullScreen();
    }
}

void TMainDisplay::DrawFps(QPainter& painter)
{
    // TODO: move fps calculation to another place, here must be only drawing
    static int frames = 0;
    static int fps = 0;
    static QTime lasttime = QTime::currentTime();

    const QTime& time = QTime::currentTime();
    if (lasttime.msecsTo(time) >= 1000) {
        fps = frames;
        frames = 0;
        lasttime = time;
    }

    const QPen penOld = painter.pen();
    DrawText(painter, QPoint(0, 10), QString("Fps: %1").arg(fps), 10);
    ++frames;
}

void TMainDisplay::DrawPing(QPainter& painter)
{
    if(Ping != 2686572)
    DrawText(painter, QPoint(0, 24), QString("Ping: %1").arg(Ping), 10);
}

void TMainDisplay::DrawText(QPainter& painter, const QPoint& pos,
                            const QString& text, int FONT_SIZE_PT = 10)
{
    // Helvetica font present on all Systems
    painter.setFont(QFont("Helvetica", FONT_SIZE_PT));
    painter.setPen(Qt::black);
    painter.drawText(pos.x() + 1, pos.y() + 1, text);
    painter.setPen(Qt::darkGray);
    painter.drawText(pos.x(), pos.y(), text);
}

// Detecting our coordinates
QPoint TMainDisplay::GetPlayerCoordinatesAndPing() {
    QPoint res;
    size_t playerId = Application->GetNetwork()->GetId();
    for (int i = 0; i != CurrentWorld->players_size(); i++) {
        const Epsilon5::Player &player = CurrentWorld->players(i);
        if ((size_t)player.id() == playerId) {
            res.setX(player.x());
            res.setY(player.y());
            if (player.has_ping()) {
                Ping = player.ping();
            }
        }
    }
    return res;
}

QPoint TMainDisplay::GetCursorPos()
{
    return this->mapFromGlobal(QCursor::pos());
}

QPoint TMainDisplay::GetCenter() {
    return QPoint(width() / 2, height() / 2);
}

void TMainDisplay::DrawPlayers(QPainter& painter, QPainter& miniMap,
                               const QPoint& playerPos, const QPoint &widgetCenter)
{
    // Players drawing
    const int nickMaxWidth = 200;
    const QImage* img;
    const QFont oldFont = painter.font();
    const QPen oldPen = painter.pen();
    QFont nickFont(oldFont);
    nickFont.setBold(true);
    nickFont.setPointSize(12);
    for (int i = 0; i != CurrentWorld->players_size(); i++) {
        const Epsilon5::Player &player = CurrentWorld->players(i);
        QPoint pos = QPoint(player.x(), player.y()) - playerPos;
        QString nickName;
        if (player.has_name()) { // New player
            nickName = player.name().c_str();
            PlayerNames[player.id()] = nickName;
        } else {
            if (PlayerNames.find(player.id()) != PlayerNames.end()) {
                nickName = PlayerNames[player.id()];
            }
        }

        if (nickName.isEmpty()) {
            Control.set_need_full(true);
        } else {
            Control.set_need_full(false);
        }

        size_t hp = player.hp();

        // Set player or enemy image
        if ((size_t)player.id() == Application->GetNetwork()->GetId()) {
            img = &Images->GetImage("player");
            miniMap.setPen(Qt::red);
            miniMap.setBrush(Qt::red);
            nickName += " - " + QString::number(hp) + "%";
        } else {
            // Get team image
            if (player.team()) {
                img = &Images->GetImage("peka_t2");
                miniMap.setPen(Qt::blue);
                miniMap.setBrush(Qt::blue);
            } else {
                img = &Images->GetImage("peka_t1");
                miniMap.setPen(Qt::yellow);
                miniMap.setBrush(Qt::yellow);
            }
        }
        miniMap.drawEllipse(Map->GetObjectPosOnMinimap(
                QPoint(player.x(), player.y()), MAX_MINIMAP_SIZE), 1, 1);

        painter.drawImage(widgetCenter.x() + pos.x() - img->width() / 2,
                          widgetCenter.y() + pos.y() - img->height() / 2, *img);

        // Draw player name
        painter.setPen(miniMap.pen());
        painter.setFont(nickFont);
        QRect nickRect = QRect(widgetCenter.x() + pos.x() - nickMaxWidth/2,
                        widgetCenter.y() + pos.y() - img->height()/2
                               - painter.fontInfo().pixelSize()-5,
                        nickMaxWidth, painter.fontInfo().pixelSize() + 2);

        painter.drawText(nickRect, Qt::AlignTop | Qt::AlignHCenter, nickName);
        painter.setPen(oldPen);
        painter.setFont(oldFont);
    }
}

void TMainDisplay::DrawBullets(QPainter& painter, const QPoint& playerPos,
                               const QPoint& widgetCenter)
{
    const QImage* img;
    for (int i = 0; i != CurrentWorld->bullets_size(); i++) {
        const Epsilon5::Bullet &bullet = CurrentWorld->bullets(i);
        QPoint currentBulletPos(bullet.x(), bullet.y());
        QPoint pos = GetCorrect(playerPos, currentBulletPos);

        switch (bullet.bullet_type()) {
        case Epsilon5::Bullet_Type_ARBUZ:
            img = &Images->GetImage("arbuz");
            break;
        case Epsilon5::Bullet_Type_LITTLE_BULLET:
            img = &Images->GetImage("bullet");
            break;
        default:
            throw UException("Unknown bullet");
            break;
        }

        painter.drawImage(widgetCenter.x() + pos.x() - img->width() / 2,
                          widgetCenter.y() + pos.y() - img->height() / 2, *img);
    }
}

void TMainDisplay::DrawObjects(QPainter& painter, QPainter& miniMap,
        const QPoint& playerPos, const QPoint& widgetCenter)
{
    const QImage* img;
    for (int i = 0; i != CurrentWorld->objects_size(); i++) {
        const Epsilon5::Object& object = CurrentWorld->objects(i);

        QPoint currentObjectPos(object.x(), object.y());
        QPoint pos = GetCorrect(playerPos, currentObjectPos);

        // BUG: Type of ID mismatch (int32 vs size_t on server)
        if( object.id() < 0 )
            continue;

        img = Objects->GetImageById(object.id());
        QTransform transform;
        transform.rotate(object.angle() * 180 / M_PI);
        QImage rimg = img->transformed(transform);

        painter.drawImage(widgetCenter.x() + pos.x() - rimg.width() / 2,
                          widgetCenter.y() + pos.y() - rimg.height() / 2, rimg);

        QPoint posOnMinimap(Map->GetObjectPosOnMinimap(
                currentObjectPos, MAX_MINIMAP_SIZE));
        miniMap.drawImage(posOnMinimap.x() - 4, posOnMinimap.y() - 4,
                rimg.scaledToHeight(4));
    }
}

void TMainDisplay::DrawRespPoints(QPainter& painter, QPainter& miniMap,
        const QPoint& playerPos, const QPoint& widgetCenter)
{
    const QImage* img;
    if (CurrentWorld->resp_points_size() > 0) {
        RespPoints.clear();
        for (int i = 0; i < CurrentWorld->resp_points_size(); i++) {
            TRespPoint pos;
            pos.X = CurrentWorld->resp_points(i).x();
            pos.Y = CurrentWorld->resp_points(i).y();
            pos.Team = (ETeam)(CurrentWorld->resp_points(i).team());
            RespPoints.push_back(pos);
        }
    }

    for (int i = 0; i < RespPoints.size(); i++) {
        if (RespPoints[i].Team == T_One) {
            img = &Images->GetImage("flag_t1");
        } else if (RespPoints[i].Team == T_Second) {
            img = &Images->GetImage("flag_t2");
        } else {
            img = &Images->GetImage("flag_tn");
        }
        QPoint currentRespPos(RespPoints[i].X, RespPoints[i].Y);
        QPoint pos = GetCorrect(playerPos, currentRespPos);
        painter.drawImage(widgetCenter.x() + pos.x() - img->width() / 2,
                          widgetCenter.y() + pos.y() - img->height() / 2, *img);
        QPoint posOnMinimap(Map->GetObjectPosOnMinimap(
                currentRespPos, MAX_MINIMAP_SIZE));
        miniMap.drawImage(posOnMinimap.x(), posOnMinimap.y() - 10,
                (*img).scaled(10, 10));
    }
}

void TMainDisplay::DrawStats(QPainter& painter) {
    if (CurrentWorld->players_stat_size() > 0) {
        Stats.clear();
        for (int i = 0; i < CurrentWorld->players_stat_size(); i++) {
            TPlayerStat stat;
            stat.Id = CurrentWorld->players_stat(i).id();
            stat.Score = CurrentWorld->players_stat(i).score();
            stat.Kills = CurrentWorld->players_stat(i).kills();
            stat.Deaths = CurrentWorld->players_stat(i).deaths();
            Stats.push_back(stat);
        }
    }

    if (!Stats.empty() && ShowStats) {
        QPoint widgetCenter(width() / 2, height() / 2);


        QFont font("Helvetica", 18);
        QImage statsImg(400, Stats.size() * font.weight()/2, QImage::Format_ARGB32);
        statsImg.fill(qRgba(255, 255, 255, 100));
        painter.drawImage(widgetCenter.x() - 200, widgetCenter.y() - Stats.size() * font.weight(), statsImg);

        painter.setFont(font);
        painter.setPen(Qt::black);

        QPoint startPos(widgetCenter.x() - 150, widgetCenter.y() - Stats.size() * font.weight() + font.weight() / 2);

        for (auto i = 0; i < Stats.size(); i++) {
            QString statStr = QString("%1\t%2 - %3 - %4")
                    .arg(PlayerNames[Stats[i].Id])
                    .arg(Stats[i].Score)
                    .arg(Stats[i].Kills)
                    .arg(Stats[i].Deaths);
            painter.drawText(startPos.x(), startPos.y() + i * font.weight() / 2, statStr);
        }
    }
}

void TMainDisplay::DrawWorld(QPainter& painter){
    if( !CurrentWorld )
        return;

    try {
        QPoint widgetCenter(width() / 2, height() / 2);
        QPoint playerPos = GetPlayerCoordinatesAndPing();

        Map->DrawBackground(playerPos, size(), painter);

        // Prepare minimap painter
        // TODO: minimap image creation should be moved into new class
        //       and inited on map loading process (not every frame)
        QImage miniMapImg(Map->GetMinimapSize(MAX_MINIMAP_SIZE), QImage::Format_ARGB32);
        miniMapImg.fill(qRgba(255, 255, 255, 100));
        QPainter miniMap(&miniMapImg);
        miniMap.drawRect(0, 0, miniMapImg.width() - 1, miniMapImg.height() - 1);

        // Drawing staff
        DrawBullets(painter, playerPos, widgetCenter);
        DrawObjects(painter, miniMap, playerPos, widgetCenter);
        DrawPlayers(painter, miniMap, playerPos, widgetCenter);
        DrawRespPoints(painter, miniMap, playerPos, widgetCenter);
        DrawStats(painter);

        // Minimap drawing
        painter.drawImage(10, 30, miniMapImg);

        if (Application->GetState() == ST_SelectingResp) {
            // TODO - Draw resp menu
        }

        // Detect targeting angle for Control packet
        QPoint cursorPos = this->mapFromGlobal(QCursor::pos());
        double angle = getAngle(cursorPos - widgetCenter);
        Control.set_angle(angle);

        this->update();
    } catch (const std::exception& e) {
        qDebug() << Q_FUNC_INFO << ": " << e.what();
    }
}
