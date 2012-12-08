// main.cpp
#include "global.h"
#include "application.h"
#include "mainwindow.h"

#include "storage/st_mapcontainer.h"
//------------------------------------------------------------------------------
// Global variables inittialization
TSettings* settings = Global::Settings();
//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    containers::TMapContainer maps;
    containers::TRespawnContainer respawns;
    return 0;

    TApplication app(argc, argv);
    TMainWindow window;
    window.show();
    app.exec();
    return 0;
}
//------------------------------------------------------------------------------
