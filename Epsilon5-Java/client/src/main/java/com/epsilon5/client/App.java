package com.epsilon5.client;

import com.google.inject.Guice;
import com.google.inject.Injector;
import com.epsilon5.client.modules.AppModule;
import com.epsilon5.client.network.NetworkChannel;
import com.epsilon5.client.window.Window;

public class App {

    public static void main(String[] args) {
        final Injector injector = Guice.createInjector(new AppModule());
        final Window window = injector.getInstance(Window.class);
        window.show();

        final NetworkChannel channel = injector.getInstance(NetworkChannel.class);
        channel.open();
    }
}
