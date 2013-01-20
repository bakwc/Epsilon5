package com.epsilon5.client.world;

import com.epsilon5.client.network.Protocol;

class BulletDrawable implements Drawable {

    private Protocol.Bullet bullet;

    public void init(Protocol.Bullet bullet) {
        this.bullet = bullet;
    }

    @Override
    public int getX() {
        return bullet.getX();
    }

    @Override
    public int getY() {
        return bullet.getY();
    }

    @Override
    public int getLayer() {
        return 5;
    }

    @Override
    public int getSpriteId() {
        return 104;
    }
}
