#pragma once

#include <memory>
#include <functional>

#include "Epsilon5.pb.h"

class World
{
public:
    World();
    ~World();

    void setUpdateFunc(const std::function<void()>& func);

    void update(std::shared_ptr<Epsilon5::World> message);
    void update(std::shared_ptr<Epsilon5::PlayerInfo> message);

    Epsilon5::World* getWorld();
    Epsilon5::PlayerInfo* getPlayerInfo();

private:
    std::shared_ptr<Epsilon5::World> mWorld;
    std::shared_ptr<Epsilon5::PlayerInfo> mPlayerInfo;
    std::function<void()> mUpdateFunc;
};
