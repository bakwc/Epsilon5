#include "Context.h"

#include "Settings.h"
#include "World/World.h"
#include "Network/MessageProcessor.h"
#include "Network/NetworkService.h"
#include "World/Controller.h"

Context::Context() {
    mSettings.reset(new Settings);
    mWorld.reset(new World);
    mMessageProcessor.reset(new MessageProcessor(mWorld.get()));
    mNetworkService.reset(new NetworkService(mMessageProcessor.get()));
    mController.reset(new Controller(mNetworkService.get()));
}

Context::~Context() {
}

template <typename T>
T* Context::get() {
    static_assert(false, "Not implemented yet.");
}

template <>
Settings* Context::get() {
    return mSettings.get();
}

template <>
World* Context::get() {
    return mWorld.get();
}

template <>
MessageProcessor* Context::get() {
    return mMessageProcessor.get();
}

template <>
NetworkService* Context::get() {
    return mNetworkService.get();
}

template <>
Controller* Context::get() {
    return mController.get();
}
