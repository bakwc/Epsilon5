#include "application.h"

TApplication::TApplication(int& argc, char *argv[])
    : QCoreApplication(argc, argv)
    , World(new TWorld(this))
    , Server(new TServer(this))
    , Objects(new TObjects(this))
    , Maps(new TMaps(this))
{
    connect(Server, SIGNAL(NewPlayer(size_t)),
            World, SLOT(PlayerEnter(size_t)));

    connect(Server, SIGNAL(PlayerDisconnected(size_t)),
            World, SLOT(PlayerExit(size_t)));

    connect(Maps, SIGNAL(SpawnObject(size_t,int,int,double)),
            World, SLOT(SpawnObject(size_t,int,int,double)));

    connect(Maps, SIGNAL(SpawnBorders(QSize)),
            World, SLOT(SpawnBorders(QSize)));

    connect(Maps, SIGNAL(ClearObjects()),
            World, SLOT(ClearObjects()));

    connect(Maps, SIGNAL(ClearBorders()),
            World, SLOT(ClearBorders()));
}

bool TApplication::Init() {
    Objects->LoadObjects("objects/objects.txt");
    Maps->LoadMaplist("maplist.txt");
    Maps->LoadNextMap();
    if (Server->Start()) {
        World->Start();
        return true;
    }
    return false;
}
