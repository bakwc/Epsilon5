#pragma once

#include <memory>

#include "cocos2d.h"

#include "Epsilon5.pb.h"

class NetworkService;

class Controller
{
public:
    Controller(NetworkService* service);
    ~Controller();

    void tick();
    void updateTouch(bool isDown);
    void updateAngle(float x, float y);
    void updateAcceleration(cocos2d::CCAcceleration* acceleration);

private:
    NetworkService* mNetworkService;
    Epsilon5::Control mControl;
};
