package com.epsilon5.client.network;

import com.google.inject.Inject;
import com.google.inject.Provider;
import com.google.inject.Singleton;
import com.epsilon5.client.settings.NetworkSettings;
import org.jboss.netty.bootstrap.ClientBootstrap;
import org.jboss.netty.channel.ChannelFuture;
import org.jboss.netty.channel.ChannelPipeline;
import org.jboss.netty.channel.ChannelPipelineFactory;
import org.jboss.netty.channel.Channels;
import org.jboss.netty.channel.socket.nio.NioDatagramChannelFactory;

import java.net.InetSocketAddress;
import java.util.concurrent.Executors;

@Singleton
public class NetworkChannel implements AutoCloseable {

    private final Provider<MessageHandler> handler;

    private final ClientBootstrap bootstrap;
    private ChannelFuture future;

    private final ChannelPipelineFactory pipelineFactory = new ChannelPipelineFactory() {

        @Override
        public ChannelPipeline getPipeline() throws Exception {
            return Channels.pipeline(
                    new NetworkEncoder(),
                    new NetworkDecoder(),
                    handler.get());
        }
    };

    @Inject
    private NetworkChannel(NetworkSettings settings, Provider<MessageHandler> handler) {
        this.handler = handler;

        bootstrap = new ClientBootstrap(new NioDatagramChannelFactory(
                Executors.newSingleThreadExecutor()));
        bootstrap.setPipelineFactory(pipelineFactory);

        bootstrap.setOption("tcpNoDelay", true);
        bootstrap.setOption("keepAlive", true);
        bootstrap.setOption("remoteAddress",
                new InetSocketAddress(settings.getHost(), settings.getPort()));
    }

    public void open() {
        future = bootstrap.connect();
    }

    @Override
    public void close() {
        if (future != null) {
            if (!future.isDone()) {
                future.cancel();
            }

            if (future.isSuccess()) {
                future.getChannel().close().awaitUninterruptibly();
            }
        }
        bootstrap.releaseExternalResources();
    }

}
