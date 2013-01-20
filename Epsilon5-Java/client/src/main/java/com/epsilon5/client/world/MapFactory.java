package com.epsilon5.client.world;

import com.google.inject.Singleton;
import com.epsilon5.client.map.Map;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;
import java.io.File;

@Singleton
class MapFactory {

    public Map create(String name) {
        try {
            final JAXBContext context = JAXBContext.newInstance(Map.class);
            final Unmarshaller um = context.createUnmarshaller();
            final File file = new File("maps/" + name + ".xml");
            return (Map) um.unmarshal(file);
        } catch (JAXBException e) {
            throw new IllegalArgumentException(e);
        }
    }

}
