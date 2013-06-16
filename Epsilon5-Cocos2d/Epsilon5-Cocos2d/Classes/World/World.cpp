#include "World.h"

World::World() {
}

World::~World() {
}

void World::update(std::shared_ptr<Epsilon5::World> message) {
    mWorld = message;
}

void World::update(std::shared_ptr<Epsilon5::PlayerInfo> message) {
    mPlayerInfo = message;
}
