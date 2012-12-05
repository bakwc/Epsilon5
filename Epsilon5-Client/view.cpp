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
#include <QGLWidget>
#include <exception>
#include <QBrush>

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

//    setViewport(new QGLWidget);

    Control.set_angle(0);
    Control.mutable_keystatus()->set_keyattack1(false);
    Control.mutable_keystatus()->set_keyattack2(false);
    Control.mutable_keystatus()->set_keyleft(false);
    Control.mutable_keystatus()->set_keyright(false);
    Control.mutable_keystatus()->set_keyup(false);
    Control.mutable_keystatus()->set_keydown(false);

    setScene(Scene);
//    Scene->setSceneRect(0, 0,
//    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

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
    static bool b = 0;

    if (CurrentWorld) {
//        qDebug() << Q_FUNC_INFO;

        if (!b) {
            Scene->setBackgroundBrush(QBrush(Map->GetBackground()));
            b = 1;
        }
        try {
//            Scene->setBackgroundBrush(QBrush(Map->GetBackground()));


        // Arrangment players
        for (int i=0; i != CurrentWorld->players_size(); ++i) {
            const Epsilon5::Player &player = CurrentWorld->players(i);

            // Create item, if it is not exist in scene
            TPlayerItem *pItem = (TPlayerItem*)Scene->GetItem(TPlayerItem::PLAYER, player.id());
            if (!pItem) {
                pItem = dynamic_cast<TPlayerItem*>(Scene->AddItem(new TPlayerItem, player.id()));
            }

            // Set pixmap
            QPixmap pix;
            if (player.id() == App->GetNetwork()->GetId())
                pItem->SetPix(Images->GetImage("player"));
            else
                pItem->SetPix(Images->GetImage("enemy"));

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

            // Set pixmap
            bItem->SetPix(Images->GetImage("bullet"));
            // Set item's position
            bItem->setPos(bullet.x(), bullet.y());
        }

        // Arrangment objects
//        Scene->ClearItems(TObjectItem::OBJECT);
        for (int i=0; i != CurrentWorld->bullets_size(); ++i) {
            const Epsilon5::Object& object = CurrentWorld->objects(i);

            // Create item, if it is not exist in scene
            TObjectItem* oItem = (TObjectItem*)Scene->GetItem(TObjectItem::OBJECT, object.id());
            if (!oItem) {
                oItem = (TObjectItem*)Scene->AddItem(new TObjectItem, object.id());
            }

            // Set pixmap
            qDebug() << "Image id:" << object.id();
//            QPixmap pix = QPixmap::fromImage(*Objects->GetImageById(object.id()));
            oItem->SetPix(*Objects->GetImageById(object.id()));
            // Set position
            oItem->setPos(object.x(), object.y());
        }

        update();

        } catch (std::exception& e) {
            update();
            qDebug() << Q_FUNC_INFO << e.what();
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
