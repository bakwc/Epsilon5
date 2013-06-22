#pragma once

#include <memory>

class Settings;
class World;
class MessageProcessor;
class NetworkService;
class Controller;

class Context
{
public:
    Context();
    ~Context();

    template <typename T>
    T* get();

private:
    std::unique_ptr<Settings> mSettings;
    std::unique_ptr<World> mWorld;
    std::unique_ptr<MessageProcessor> mMessageProcessor;
    std::unique_ptr<NetworkService> mNetworkService;
    std::unique_ptr<Controller> mController;
};
