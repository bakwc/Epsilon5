#pragma once

#include <QApplication>
#include "maindisplay.h"
#include "network.h"

class TApplication : public QApplication
{
    Q_OBJECT
public:
    TApplication(int argc, char *argv[]);
    bool Init();
    inline TMainDisplay* GetMainDisplay() {
        return &MainDisplay;
    }
    inline TNetwork* GetNetwork() {
        return Network;
    }
private:
    TMainDisplay MainDisplay;
    TNetwork* Network;
};
