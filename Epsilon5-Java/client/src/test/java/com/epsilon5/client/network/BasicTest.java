package com.epsilon5.client.network;

import org.junit.Assert;
import org.junit.Test;

public class BasicTest {

    @Test
    public void testSomething() {
        Assert.assertEquals(PacketType.fromMessage(Protocol.World.getDefaultInstance()), PacketType.WORLD);
    }

    @Test
    public void testEncoding() throws Exception{
        final NetworkEncoder encoder = new NetworkEncoder();
        final NetworkDecoder decoder = new NetworkDecoder();

        final Protocol.Auth message = Protocol.Auth.newBuilder()
                .setName("test")
                .setPassword("test")
                .build();

        Assert.assertEquals(decoder.decode(null, null, encoder.encode(null, null, message)), message);
    }
}
