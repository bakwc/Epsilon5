package com.epsilon5.client.network;

import com.google.inject.Inject;
import com.google.inject.Injector;
import com.google.inject.Singleton;
import com.epsilon5.client.settings.PlayerSettings;
import org.jboss.netty.channel.Channel;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

@Singleton
public class MessageSender {

    private final Logger logger = LoggerFactory.getLogger(MessageSender.class);

    private final Injector injector;
    private Channel channel;

    private int packetNumber;

    @Inject
    private MessageSender(Injector injector) {
        this.injector = injector;
    }

    public void setChannel(Channel channel) {
        this.channel = channel;
    }

    public void sendAuth() {
        final PlayerSettings settings = injector.getInstance(PlayerSettings.class);

        final Protocol.Auth message = Protocol.Auth.newBuilder()
                .setName(settings.getName())
                .setPassword(settings.getPassword())
                .build();

        logger.trace("Auth message is sent, {}", message);
        channel.write(message);
    }

    public void sendControl(Protocol.Control.Builder builder) {
        if (channel != null) {
            builder.setPacketNumber(++packetNumber);

            final Protocol.Control message = builder.build();
            logger.trace("Control message is sent, {}", message);
            channel.write(message);
        } else {
            logger.trace("Control message isn't sent");
        }
    }

}
