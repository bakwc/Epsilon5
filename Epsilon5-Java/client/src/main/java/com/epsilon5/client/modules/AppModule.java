package com.epsilon5.client.modules;

import com.google.inject.Binder;
import com.google.inject.Module;
import com.google.inject.TypeLiteral;
import com.google.inject.matcher.Matchers;
import com.google.inject.spi.TypeEncounter;
import com.google.inject.spi.TypeListener;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class AppModule implements Module {

    private final Logger logger = LoggerFactory.getLogger(AppModule.class);

    @Override
    public void configure(Binder binder) {
        binder.bindListener(Matchers.any(), new TypeListener() {
            @Override
            public <I> void hear(TypeLiteral<I> type, TypeEncounter<I> encounter) {
                logger.debug("{} is created", type.getRawType().getName());
            }
        });

        binder.install(new DescriptionModule());
    }

}
