#include "application.h"

Application::Application(int argc, char *argv[]):
    QApplication(argc, argv)
{
}

bool Application::init()
{
    _mainDisplay.show();
    return true;
}
