#include "application.h"

TApplication::TApplication(int& argc, char *argv[])
    : QCoreApplication(argc, argv)
    , World(new TWorld(this))
    , Server(new TServer(this))
{
    connect(Server, SIGNAL(NewPlayer(quint32)),
            World, SLOT(PlayerEnter(quint32)));

    connect(Server, SIGNAL(PlayerDisconnected(quint32)),
            World, SLOT(PlayerExit(quint32)));
}

bool TApplication::Init() {
    if (Server->Start()) {
        World->Start();
        return true;
    }
    return false;
}
