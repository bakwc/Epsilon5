#include "Controller.h"

#include <cmath>

#include "Network/NetworkService.h"

Controller::Controller(NetworkService* service)
    : mNetworkService(service)
{
    mControl.set_angle(0);
    mControl.mutable_keystatus()->set_keyattack1(false);
    mControl.mutable_keystatus()->set_keyattack2(false);
    mControl.mutable_keystatus()->set_keyleft(false);
    mControl.mutable_keystatus()->set_keyright(false);
    mControl.mutable_keystatus()->set_keyup(false);
    mControl.mutable_keystatus()->set_keydown(false);
    mControl.mutable_keystatus()->set_keyenter(false);
    mControl.set_weapon(Epsilon5::Pistol);
}

Controller::~Controller() {
}

void Controller::tick() {
    mControl.set_packet_number(mNetworkService->makePacketNumber());
    mNetworkService->send(PacketType::Control, mControl);
}

void Controller::updateTouch(bool isDown) {
    mControl.mutable_keystatus()->set_keyattack1(isDown);
}

void Controller::updateAngle(float x, float y) {
    static const double pi = std::atan2(0,-1);
    double angle;
    if (x > 0) {
        angle = std::atan(y / x);
    } else if (x < 0 && y > 0) {
        angle = pi + std::atan(y / x);
    } else if (x < 0 && y < 0) {
        angle = -pi + std::atan(y / x);
    } else if (x == 0 && y > 0) {
        angle = pi / 2;
    } else {
        angle = -pi / 2;
    }
    mControl.set_angle(angle);
}

void Controller::updateAcceleration(cocos2d::CCAcceleration* acceleration) {
    mControl.mutable_keystatus()->set_keyleft(acceleration->x > 0);
    mControl.mutable_keystatus()->set_keyright(acceleration->x < 0);
    mControl.mutable_keystatus()->set_keyup(acceleration->y < 0);
    mControl.mutable_keystatus()->set_keydown(acceleration->y > 0);
    mControl.mutable_keystatus()->set_keyenter(acceleration->z > 0);
}
