#pragma once

#include <memory>

#include "PacketType.h"
#include "Epsilon5.pb.h"

class World;

class MessageProcessor {
public:
    MessageProcessor(World* world);
    ~MessageProcessor();

    void process(PacketType type, void* data, int size);

private:
    World* mWorld;

private:
    template <typename Message>
    void process(PacketType type, PacketType expected, void* data, int size);

    template <typename Message>
    void process(const std::shared_ptr<Message>& message);
};
