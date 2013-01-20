package com.epsilon5.client.world;

import com.google.inject.Inject;
import com.google.inject.Singleton;
import com.epsilon5.client.map.Map;
import com.epsilon5.client.network.Protocol;

@Singleton
public class CurrentWorld {

    private final MapFactory mapFactory;
    private Map map;

    private Protocol.World world;
    private Protocol.PlayerInfo playerInfo;

    private Protocol.Player hero;

    private final BackgroundDrawable backgroundDrawable = new BackgroundDrawable();
    private final PlayerDrawable playerDrawable = new PlayerDrawable();
    private final BulletDrawable bulletDrawable = new BulletDrawable();

    @Inject
    private CurrentWorld(MapFactory mapFactory) {
        this.mapFactory = mapFactory;
    }

    // TODO synchronize
    public void setWorld(Protocol.World world) {
        this.world = world;
//        if (world.hasPlayerInfo()) {
//            playerInfo = world.getPlayerInfo();
//        }

        for (Protocol.Player player : world.getPlayersList()) {
            if (player.getId() == playerInfo.getId()) {
                hero = player;
                break;
            }
        }
    }

    public void setPlayerInfo(Protocol.PlayerInfo playerInfo) {
        this.playerInfo = playerInfo;

        backgroundDrawable.init(mapFactory.create(playerInfo.getMap()).getBackground());
    }

    public boolean isDrawable() {
        return world != null && hero != null;
    }

    public Protocol.Player getHero() {
        return hero;
    }

    public Drawable getBackgroundDrawable() {
        return backgroundDrawable;
    }

    public int getPlayerCount() {
        return world.getPlayersCount();
    }

    public Drawable getPlayerDrawable(int index) {
        playerDrawable.init(world.getPlayers(index));
        return playerDrawable;
    }

    public int getBulletCount() {
        return world.getBulletsCount();
    }

    public Drawable getBulletDrawable(int index) {
        bulletDrawable.init(world.getBullets(index));
        return bulletDrawable;
    }

}
