#pragma once

#include <memory>

#include "Epsilon5.pb.h"

class World
{
public:
    World();
    ~World();

    void update(std::shared_ptr<Epsilon5::World> message);
    void update(std::shared_ptr<Epsilon5::PlayerInfo> message);

private:
    std::shared_ptr<Epsilon5::World> mWorld;
    std::shared_ptr<Epsilon5::PlayerInfo> mPlayerInfo;
};
