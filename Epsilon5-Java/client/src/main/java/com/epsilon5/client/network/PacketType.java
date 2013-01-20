package com.epsilon5.client.network;

import com.google.protobuf.Message;

import java.io.IOException;
import java.io.InputStream;

enum PacketType {
    WORLD(Protocol.World.getDefaultInstance()),
    CONTROL(Protocol.Control.getDefaultInstance()),
    PLAYER_AUTH(Protocol.Auth.getDefaultInstance()),
    PLAYER_INFO(Protocol.PlayerInfo.getDefaultInstance()),;

    private final Message message;

    private PacketType(Message message) {
        this.message = message;
    }

    public Message makeObject(InputStream stream) throws IOException {
        return message.newBuilderForType().mergeFrom(stream).build();
    }

    public static PacketType fromMessage(Message message) {
        for (PacketType value : values()) {
            if (value.message.getClass() == message.getClass()) {
                return value;
            }
        }
        throw new IllegalArgumentException();
    }
}
