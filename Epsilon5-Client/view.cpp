#include "view.h"
#include <QImage>
#include <QPixmap>
#include <network.h>
#include "application.h"
#include "imagestorage.h"
#include "map.h"
#include "objects.h"
#include "basicitem.h"
#include "bullet.h"
#include "scene.h"

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

    startTimer(10);
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
        qDebug() << Q_FUNC_INFO;

        // Arrangment players
        for (int i=0; i != CurrentWorld->players_size(); ++i) {
            const Epsilon5::Player &player = CurrentWorld->players(i);

            // Create item, if it is not exist in scene
            if (!PlayerContains.contains(player.id())) {
                PlayerContains.insert(player.id());
                basic::BasicItem *item = new basic::BasicItem;
                scene()->addItem(item);
            }

            // Set item's position
            Scene->items().at(i)->setPos(player.x(), player.y());

            qDebug() << player.name().c_str() << player.x() << player.y();
        }

        // Arrangment bullets
        for (int i=0; i != CurrentWorld->bullets_size(); ++i) {
            const Epsilon5::Object& object = CurrentWorld->objects(i);

            // Create item, if it is not exist in scene
            if (!ObjectContains.contains(object.id())) {
                ObjectContains.insert(object.id());
                basic::BasicItem *item = new basic::Bullet;
//                Scene->addItem(item);
            }

            // Set item's position

        }
    }
}

void View::RedrawWorld()
{
    CurrentWorld = &((TNetwork*)(sender()))->GetWorld();
}
