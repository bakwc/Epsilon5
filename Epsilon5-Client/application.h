#pragma once

#include <QApplication>
#include <QDateTime>
#include "maindisplay.h"
#include "network.h"
#include "settings.h"

enum EState {
    ST_MainMenu,
    ST_Connecting,
    ST_LoadingMap,
    ST_SelectingResp,
    ST_InGame
};

class TApplication : public QApplication
{
    Q_OBJECT
public:
    TApplication(int& argc, char* argv[]);
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
    inline EState GetState() {
        return State;
    }
    inline void SetState(EState state) {
        State = state;
    }
private:
    TMainDisplay MainDisplay;
    TNetwork* Network;
    TSettings* Settings;
    EState State;
};
