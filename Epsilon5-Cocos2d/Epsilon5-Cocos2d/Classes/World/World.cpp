#include "World.h"

World::World() {
}

World::~World() {
}

void World::update(std::shared_ptr<Epsilon5::World> message) {
    puts("World");
    mWorld = message;
}

void World::update(std::shared_ptr<Epsilon5::PlayerInfo> message) {
    puts("PlayerInfo");
    mPlayerInfo = message;
}
