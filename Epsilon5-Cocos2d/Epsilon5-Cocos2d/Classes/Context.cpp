#include "Context.h"

#include "Settings.h"
#include "World/World.h"
#include "Network/MessageProcessor.h"
#include "Network/NetworkService.h"

#define SINGLETON(className, ...) \
    (m##className ? m##className : m##className = std::make_shared<className>(__VA_ARGS__))

Context::Context() {
}

Context::~Context() {
}

template <>
std::shared_ptr<Settings> Context::get() {
    return SINGLETON(Settings);
}

template <>
std::shared_ptr<World> Context::get() {
    return SINGLETON(World);
}

template <>
std::shared_ptr<MessageProcessor> Context::get() {
    return SINGLETON(MessageProcessor, get<World>());
}

template <>
std::shared_ptr<NetworkService> Context::get() {
    return SINGLETON(NetworkService, get<MessageProcessor>());
}
