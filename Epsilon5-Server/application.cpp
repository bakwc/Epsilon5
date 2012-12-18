#include <ctime>
#include "../utils/uexception.h"
#include "application.h"

TApplication::TApplication(int& argc, char *argv[])
    : QCoreApplication(argc, argv)
{
    connect(Server, SIGNAL(NewPlayer(size_t, ETeam)),
            World, SLOT(PlayerSpawn(size_t, ETeam)));

    connect(Server, SIGNAL(PlayerDisconnected(size_t)),
            World, SLOT(PlayerKill(size_t)));

    connect(Server, SIGNAL(PlayerDisconnected(size_t)),
            World, SLOT(NeedFullPacket()));

    connect(Maps, SIGNAL(SpawnObject(size_t, int, int, double)),
            World, SLOT(SpawnObject(size_t, int, int, double)));

    connect(Maps, SIGNAL(SpawnBorders(QSize)),
            World, SLOT(SpawnBorders(QSize)));

    connect(Maps, SIGNAL(ClearObjects()),
            World, SLOT(ClearObjects()));

    connect(Maps, SIGNAL(ClearBorders()),
            World, SLOT(ClearBorders()));

    connect(Maps, SIGNAL(MapLoaded()),
            World, SLOT(NeedFullPacket()));

    connect(WeaponPacks, SIGNAL(SpawnBullet(TBullet*)),
            World, SLOT(SpawnBullet(TBullet*)));

    connect(World, SIGNAL(PlayerKilled(size_t)),
            Server, SIGNAL(PlayerKilled(size_t)));
}

void TApplication::Init() {
    srand(time(0));
    Objects->LoadObjects("objects/objects.txt");
    Maps->LoadMaps();
    Maps->LoadNextMap();
    Server->Start();
    World->Start();
}
