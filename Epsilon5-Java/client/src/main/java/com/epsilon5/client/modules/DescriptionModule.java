package com.epsilon5.client.modules;

import com.google.inject.Binder;
import com.google.inject.Module;
import com.epsilon5.client.settings.NetworkSettings;
import com.epsilon5.client.settings.PlayerSettings;
import com.epsilon5.client.settings.Settings;
import com.epsilon5.client.settings.WindowSettings;
import com.epsilon5.client.world.Sprites;
import com.epsilon5.client.world.World;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;
import java.io.File;

class DescriptionModule implements Module {

    @Override
    public void configure(Binder binder) {
        try {
            final JAXBContext context = JAXBContext.newInstance(Settings.class, World.class);
            final Unmarshaller um = context.createUnmarshaller();

            final Settings settings = (Settings) um.unmarshal(new File("description/settings.xml"));
            binder.bind(WindowSettings.class).toInstance(settings.getWindow());
            binder.bind(NetworkSettings.class).toInstance(settings.getNetwork());
            binder.bind(PlayerSettings.class).toInstance(settings.getPlayer());

            final World world = (World) um.unmarshal(new File("description/world.xml"));
            binder.bind(Sprites.class).toInstance(world.getSprites());

        } catch (JAXBException e) {
            binder.addError(e);
        }
    }

}
