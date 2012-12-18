#pragma once

#include <QCoreApplication>
#include <QByteArray>
#include "world.h"
#include "server.h"
#include "objects.h"
#include "maps.h"
#include "weaponpacks.h"
#include "settings.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT
public:
    TApplication(int& argc, char *argv[]);
    void Init();
    inline TSettings* GetSettings() {
        return Settings;
    }
    inline TWorld* GetWorld() {
        return World;
    }
    inline TObjects* GetObjects() {
        return Objects;
    }
    inline TMaps* GetMaps() {
        return Maps;
    }
    inline TWeaponPacks* GetWeaponPacks() {
        return WeaponPacks;
    }
    inline TServer* GetServer() {
        return Server;
    }
private:
    TSettings* Settings = new TSettings(this);
    TWorld* World = new TWorld(this);
    TServer* Server = new TServer(this);
    TObjects* Objects = new TObjects(this);
    TMaps* Maps = new TMaps(this);
    TWeaponPacks* WeaponPacks = new TWeaponPacks(this);
};
