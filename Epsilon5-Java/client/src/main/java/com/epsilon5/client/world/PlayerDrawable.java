package com.epsilon5.client.world;

import com.epsilon5.client.network.Protocol;

class PlayerDrawable implements Drawable {

    private Protocol.Player player;

    public void init(Protocol.Player player) {
        this.player = player;
    }

    @Override
    public int getX() {
        return player.getX();
    }

    @Override
    public int getY() {
        return player.getY();
    }

    @Override
    public int getLayer() {
        return 3;
    }

    @Override
    public int getSpriteId() {
        return 101;
    }
}
