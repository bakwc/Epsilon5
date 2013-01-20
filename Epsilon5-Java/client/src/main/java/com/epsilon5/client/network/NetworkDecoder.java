package com.epsilon5.client.network;

import org.jboss.netty.buffer.ChannelBuffer;
import org.jboss.netty.buffer.ChannelBufferInputStream;
import org.jboss.netty.channel.Channel;
import org.jboss.netty.channel.ChannelHandlerContext;
import org.jboss.netty.handler.codec.oneone.OneToOneDecoder;

import java.io.InputStream;
import java.util.zip.InflaterInputStream;

class NetworkDecoder extends OneToOneDecoder {

    private static final int HEADER_SIZE = 9;

    @Override
    protected Object decode(ChannelHandlerContext ctx, Channel channel, Object msg)
            throws Exception {

        final ChannelBuffer buffer = (ChannelBuffer) msg;

        if (buffer.readableBytes() < HEADER_SIZE) {
            return null;
        }

        final PacketType packetType = PacketType.values()[buffer.readByte()];
        buffer.skipBytes(2);
        final int packedDataSize = buffer.readShort() - 4;
        buffer.skipBytes(4);

        if (buffer.readableBytes() < packedDataSize) {
            buffer.discardReadBytes();
            return null;
        }

        try (InputStream stream = new ChannelBufferInputStream(buffer, packedDataSize)) {
            return packetType.makeObject(new InflaterInputStream(stream));
        }
    }

}
