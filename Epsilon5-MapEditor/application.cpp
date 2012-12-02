// application.cpp
#include "global.h"
#include "application.h"

//------------------------------------------------------------------------------
TApplication::TApplication(int& argc, char* argv[])
    : QApplication(argc, argv) {
    Global::Settings()->Load();
}
//------------------------------------------------------------------------------
TApplication::~TApplication() {
    Global::Settings()->Save();
}
//------------------------------------------------------------------------------
