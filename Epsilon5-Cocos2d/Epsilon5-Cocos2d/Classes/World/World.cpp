#include "World.h"

World::World() {
}

World::~World() {
}

void World::setUpdateFunc(const std::function<void()>& func) {
    mUpdateFunc = func;
}

void World::update(std::shared_ptr<Epsilon5::World> message) {
    mWorld = message;
    if (mUpdateFunc)
        mUpdateFunc();
}

void World::update(std::shared_ptr<Epsilon5::PlayerInfo> message) {
    mPlayerInfo = message;
}

Epsilon5::World* World::getWorld() {
    return mWorld.get();
}

Epsilon5::PlayerInfo* World::getPlayerInfo() {
    return mPlayerInfo.get();
}
