// main.cpp
#include "global.h"
#include "application.h"
#include "mainwindow.h"
//------------------------------------------------------------------------------
// Global variables inittialization
TSettings* settings = Global::Settings();
//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    TApplication app(argc, argv);
    TMainWindow window;
    window.show();
    app.exec();
    return 0;
}
//------------------------------------------------------------------------------
