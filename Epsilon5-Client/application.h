#pragma once

#include <QApplication>
#include "maindisplay.h"
#include "network.h"
#include "settings.h"

class TApplication : public QApplication
{
    Q_OBJECT
public:
    TApplication(int& argc, char *argv[]);
    bool Init();
    inline TMainDisplay* GetMainDisplay() {
        return &MainDisplay;
    }
    inline TNetwork* GetNetwork() {
        return Network;
    }
    inline TSettings* GetSettings() {
        return Settings;
    }

private:
    TMainDisplay MainDisplay;
    TNetwork* Network;
    TSettings* Settings;
};
