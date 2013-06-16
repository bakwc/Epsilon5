#pragma once

#include <memory>

#include "cocos2d.h"

class World;
class NetworkService;

class AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();

private:
    std::shared_ptr<World> mWorld;
    std::shared_ptr<NetworkService> mNetwork;
};
