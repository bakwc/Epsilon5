#include "MessageProcessor.h"

#include "NetworkException.h"
#include "World/World.h"

MessageProcessor::MessageProcessor(World* world)
    : mWorld(world)
{
}

MessageProcessor::~MessageProcessor() {
}

void MessageProcessor::process(PacketType type, void* data, int size) {
    process<Epsilon5::World>(type, PacketType::World, data, size);
    process<Epsilon5::PlayerInfo>(type, PacketType::PlayerInfo, data, size);
}

template <typename Message>
void MessageProcessor::process(PacketType type, PacketType expected, void* data, int size) {
    if (type == expected) {
        const std::shared_ptr<Message> message(new Message);
        const bool parsed = message->ParseFromArray(data, size);
        checkNetwork(parsed);
        process(message);
    }
}

template <>
void MessageProcessor::process(const std::shared_ptr<Epsilon5::World>& message) {
    mWorld->update(message);
}

template <>
void MessageProcessor::process(const std::shared_ptr<Epsilon5::PlayerInfo>& message) {
    mWorld->update(message);
}
