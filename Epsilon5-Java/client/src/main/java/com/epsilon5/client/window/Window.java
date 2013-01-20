package com.epsilon5.client.window;

import com.google.inject.Inject;
import com.google.inject.Provider;
import com.jogamp.newt.event.WindowAdapter;
import com.jogamp.newt.event.WindowEvent;
import com.jogamp.newt.opengl.GLWindow;
import com.jogamp.opengl.util.AnimatorBase;
import com.jogamp.opengl.util.FPSAnimator;
import com.epsilon5.client.settings.NetworkSettings;
import com.epsilon5.client.settings.WindowSettings;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLProfile;

public class Window {

    private final Logger logger = LoggerFactory.getLogger(Window.class);

    private final GLWindow window;
    private final AnimatorBase animator;

    static {
        GLProfile.initSingleton();
    }

    @Inject
    private Window(WindowSettings settings,
                  Provider<Scene> sceneProvider,
                  Provider<Controller> controllerProvider) {

        final GLProfile profile = GLProfile.getDefault();
        final GLCapabilities capabilities = new GLCapabilities(profile);
        logger.info(capabilities.toString());
        window = GLWindow.create(capabilities);

        window.setSize(settings.getWidth(), settings.getHeight());
        window.setTitle(settings.getTitle());
        window.setFullscreen(settings.isFullScreen());
        window.addGLEventListener(sceneProvider.get());
        final Controller controller = controllerProvider.get();
        window.addKeyListener(controller);
        window.addMouseListener(controller);
        window.addGLEventListener(controller);

        window.addWindowListener(new WindowAdapter() {
            @Override
            public void windowDestroyNotify(WindowEvent e) {
                logger.info("Window is closed.");
                window.destroy();
                System.exit(0);
            }
        });

        animator = new FPSAnimator(window, settings.getFps());
        animator.add(window);
    }

    public void show() {
        logger.info("Window is shown.");
        window.setVisible(true);
        animator.start();
    }

}
