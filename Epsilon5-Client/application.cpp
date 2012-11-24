#include "application.h"

TApplication::TApplication(int& argc, char *argv[])
    : QApplication(argc, argv)
    , MainDisplay(this)
    , Network(new TNetwork(this))
{
    connect(Network, SIGNAL(WorldReceived()), &MainDisplay, SLOT(RedrawWorld()));
}

bool TApplication::Init() {
    MainDisplay.show();
    Network->Start();
    return true; // TODO: normal initialisation
}
