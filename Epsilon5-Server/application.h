#pragma once

#include <QCoreApplication>
#include <QByteArray>
#include "world.h"
#include "server.h"
#include "objects.h"
#include "maps.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT
public:
    TApplication(int& argc, char *argv[]);
    bool Init();
    inline TWorld* GetWorld() {
        return World;
    }
    inline TObjects* GetObjects() {
        return Objects;
    }
    inline TMaps* GetMaps() {
        return Maps;
    }
private:
    TWorld* World;
    TServer* Server;
    TObjects* Objects;
    TMaps* Maps;
};
