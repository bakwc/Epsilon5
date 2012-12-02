// application.h
#pragma once
#include <QApplication>
//------------------------------------------------------------------------------
class TApplication : public QApplication {
public:
    TApplication(int& argc, char* argv[]);
    ~TApplication();
};
//------------------------------------------------------------------------------
