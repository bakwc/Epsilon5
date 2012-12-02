#include "application.h"
#include "view.h"

TApplication::TApplication(int& argc, char *argv[])
    : QApplication(argc, argv)
    , MainDisplay(this)
    , Network(new TNetwork(this))
    , Settings(new TSettings(this))
{
//    connect(Network, SIGNAL(WorldReceived()), &MainDisplay, SLOT(RedrawWorld()));
}

bool TApplication::Init() {
//    MainDisplay.Init();
//    MainDisplay.show();
    View_ = new View(this);
    connect(Network, SIGNAL(WorldReceived()), View_, SLOT(RedrawWorld()));
    View_->Init();
    View_->show();
    Network->Start();
    return true; // TODO: normal initialisation
}
