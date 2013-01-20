
package com.epsilon5.client.network;

import com.google.protobuf.Message;
import org.jboss.netty.buffer.ChannelBuffer;
import org.jboss.netty.buffer.ChannelBufferOutputStream;
import org.jboss.netty.buffer.ChannelBuffers;
import org.jboss.netty.channel.Channel;
import org.jboss.netty.channel.ChannelHandlerContext;
import org.jboss.netty.handler.codec.oneone.OneToOneEncoder;

import java.io.OutputStream;
import java.util.zip.DeflaterOutputStream;

class NetworkEncoder extends OneToOneEncoder {

    private static final int HEADER_SIZE = 9;

    @Override
    protected Object encode(ChannelHandlerContext ctx, Channel channel, Object msg)
            throws Exception {

        final Message message = (Message) msg;
        final byte[] data = message.toByteArray();
        final ChannelBuffer buffer = ChannelBuffers.dynamicBuffer();

        buffer.writeByte(PacketType.fromMessage(message).ordinal());
        buffer.writeShort(data.length);
        buffer.writeShort(0);
        buffer.writeInt(0);

        try (OutputStream stream = new DeflaterOutputStream(
                new ChannelBufferOutputStream(buffer))) {

            stream.write(data);
        }


        buffer.setShort(3, buffer.capacity() - HEADER_SIZE);
        buffer.setInt(5, buffer.capacity() - HEADER_SIZE - 4);

        return buffer;
    }

}
