package com.epsilon5.client.world;

import com.epsilon5.client.map.MapBackground;

class BackgroundDrawable implements Drawable {

    private MapBackground mapBackground;

    public void init(MapBackground mapBackground) {
        this.mapBackground = mapBackground;
    }

    @Override
    public int getX() {
        return 0;
    }

    @Override
    public int getY() {
        return 0;
    }

    @Override
    public int getLayer() {
        return 8;
    }

    @Override
    public int getSpriteId() {
        return mapBackground.getSpriteId();
    }
}
