#include "application.h"

TApplication::TApplication(int& argc, char *argv[])
    : QCoreApplication(argc, argv)
    , World(new TWorld(this))
    , Server(new TServer(this))
{
    connect(Server, SIGNAL(NewPlayer(size_t)),
            World, SLOT(PlayerEnter(size_t)));

    connect(Server, SIGNAL(PlayerDisconnected(size_t)),
            World, SLOT(PlayerExit(size_t)));
}

bool TApplication::Init() {
    if (Server->Start()) {
        World->Start();
        return true;
    }
    return false;
}
