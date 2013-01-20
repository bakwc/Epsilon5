package com.epsilon5.client.network;

import com.google.inject.Inject;
import com.google.inject.Singleton;
import com.google.protobuf.Message;
import com.epsilon5.client.world.CurrentWorld;
import org.jboss.netty.channel.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

@Singleton
class MessageHandler extends SimpleChannelHandler {

    private final Logger logger = LoggerFactory.getLogger(MessageHandler.class);

    private final MessageSender sender;
    private final CurrentWorld currentWorld;

    @Inject
    private MessageHandler(MessageSender sender, CurrentWorld currentWorld) {
        this.sender = sender;
        this.currentWorld = currentWorld;
    }

    @Override
    public void channelConnected(ChannelHandlerContext ctx, ChannelStateEvent e)
            throws Exception {

        logger.info("Channel is connected");

        sender.setChannel(e.getChannel());
        sender.sendAuth();
    }

    @Override
    public void channelDisconnected(ChannelHandlerContext ctx, ChannelStateEvent e)
            throws Exception {

        logger.info("Channel is disconnected");

        sender.setChannel(null);
    }

    @Override
    public void messageReceived(ChannelHandlerContext ctx, MessageEvent e) {
        final Message message = (Message) e.getMessage();
        final PacketType packetType = PacketType.fromMessage(message);
        logger.trace("Message {} received, {}", packetType, message);
        switch (packetType) {
            case WORLD:
                currentWorld.setWorld((Protocol.World) message);
                break;
            case PLAYER_INFO:
                currentWorld.setPlayerInfo((Protocol.PlayerInfo) message);
                break;
            default:
                break;
        }
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, ExceptionEvent e) {
        logger.error("An exception caught", e.getCause());
        e.getChannel().close();
    }

}
