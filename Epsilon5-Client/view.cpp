#include "view.h"
#include <QImage>
#include <QPixmap>
#include <network.h>
#include "application.h"
#include "imagestorage.h"
#include "map.h"
#include "objects.h"

const quint16 BASE_WINDOW_WIDTH = 800;
const quint16 BASE_WINDOW_HEIGHT = 600;

View::View(TApplication *app, QWidget *parent) :
    QGraphicsView(parent),
    App(app),
    Images(new TImageStorage(this)),
    Map(new TMap(this)),
    Objects(new TObjects(this)),
    CurrentWorld(NULL),
    Scene(new QGraphicsScene)
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
}

void View::Init()
{
    Images->LoadAll();
    Objects->LoadObjects("objects/objects.txt");

    connect(App->GetNetwork(), SIGNAL(LoadMap(QString)), Map, SLOT(LoadMap(QString)));
}
