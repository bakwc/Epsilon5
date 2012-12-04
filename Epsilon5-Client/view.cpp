#include "view.h"
#include <QImage>
#include <QPixmap>
#include <network.h>
#include "application.h"
#include "imagestorage.h"
#include "map.h"
#include "objects.h"
#include "items/basicitem.h"
#include "items/tbulletitem.h"
#include "items/tplayeritem.h"
#include "items/tobjectitem.h"
#include "scene.h"
#include "QPaintEvent"
#include <QTime>
#include <QStaticText>

const quint16 BASE_WINDOW_WIDTH = 800;
const quint16 BASE_WINDOW_HEIGHT = 600;

View::View(TApplication *app, QWidget *parent) :
    QGraphicsView(parent),
    App(app),
    Images(new TImageStorage(this)),
    Map(new TMap(this)),
    Objects(new TObjects(this)),
    CurrentWorld(NULL),
    Scene(new TScene)
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

    setScene(Scene);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    startTimer(20);
}

void View::Init()
{
    Images->LoadAll();
    Objects->LoadObjects("objects/objects.txt");

    connect(App->GetNetwork(), SIGNAL(LoadMap(QString)), Map, SLOT(LoadMap(QString)));
}

View::~View()
{
}

void View::timerEvent(QTimerEvent *)
{
    if (CurrentWorld) {
//        qDebug() << Q_FUNC_INFO;

        // Arrangment players
        for (int i=0; i != CurrentWorld->players_size(); ++i) {
            const Epsilon5::Player &player = CurrentWorld->players(i);

            // Create item, if it is not exist in scene
            TPlayerItem *pItem = (TPlayerItem*)Scene->GetItem(TPlayerItem::PLAYER, player.id());
            if (!pItem) {
                pItem = dynamic_cast<TPlayerItem*>(Scene->AddItem(new TPlayerItem, player.id()));
            }

            // Set item's position
            pItem->setPos(player.x(), player.y());

//            qDebug() << player.name().c_str() << player.x() << player.y();
        }

        // Arrangment bullets
        Scene->ClearItems(TBulletItem::BULLET);
        for (int i=0; i != CurrentWorld->bullets_size(); ++i) {
            const Epsilon5::Bullet& bullet = CurrentWorld->bullets(i);

//            if (!ObjectContains.contains(object.id())) {
//                ObjectContains.insert(object.id());
//            }

            // Create item, if it is not exist in scene
            TBulletItem *bItem = (TBulletItem*)Scene->GetItem(TBulletItem::BULLET, i);
            if (!bItem) {
                bItem = (TBulletItem*)Scene->AddItem(new TBulletItem, i);
            }

            // Set item's position
            bItem->setPos(bullet.x(), bullet.y());
        }

        // Arrangment objects
        Scene->ClearItems(TObjectItem::OBJECT);
        for (int i=0; i != CurrentWorld->bullets_size(); ++i) {
            const Epsilon5::Object& object = CurrentWorld->objects(i);

            // Create item, if it is not exist in scene
            TObjectItem* oItem = (TObjectItem*)Scene->GetItem(TObjectItem::OBJECT, i);
            if (!oItem) {
                oItem = (TObjectItem*)Scene->AddItem(new TObjectItem, i);
            }

            oItem->setPos(object.x(), object.y());
        }
    }
}

void View::paintEvent(QPaintEvent *event)
{
    static QTime time;
    static int fps = 0;
    if (fps == 0)
        time.restart();
    fps += 1;

    if (time.elapsed() >= 1000) {
        qDebug() << "FPS: " << fps;
        fps = 0;
    }

    QGraphicsView::paintEvent(event);
}

void View::RedrawWorld()
{
    CurrentWorld = &((TNetwork*)(sender()))->GetWorld();
}
