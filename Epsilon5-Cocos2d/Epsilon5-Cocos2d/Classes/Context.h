#pragma once

#include <memory>

class Settings;
class World;
class MessageProcessor;
class NetworkService;

class Context
{
public:
    Context();
    ~Context();

    template <typename T>
    std::shared_ptr<T> get();

private:
    std::shared_ptr<Settings> mSettings;
    std::shared_ptr<World> mWorld;
    std::shared_ptr<MessageProcessor> mMessageProcessor;
    std::shared_ptr<NetworkService> mNetworkService;
};
