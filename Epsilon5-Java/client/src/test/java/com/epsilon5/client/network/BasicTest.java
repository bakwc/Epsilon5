package com.epsilon5.client.network;

import org.junit.Assert;
import org.junit.Test;

public class BasicTest {
    @Test
    public void testSomething() {
        Assert.assertEquals(PacketType.fromMessage(Protocol.World.getDefaultInstance()), PacketType.WORLD);
    }
}
