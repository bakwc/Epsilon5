package com.epsilon5.client.window;

import com.google.inject.Inject;
import com.jogamp.newt.event.KeyEvent;
import com.jogamp.newt.event.KeyListener;
import com.jogamp.newt.event.MouseEvent;
import com.jogamp.newt.event.MouseListener;
import com.epsilon5.client.network.MessageSender;
import com.epsilon5.client.network.Protocol;

import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLEventListener;
import java.util.Timer;
import java.util.TimerTask;

class Controller implements KeyListener, MouseListener, GLEventListener {

    private final MessageSender sender;

    private final Protocol.Control.Builder control = Protocol.Control.newBuilder();
    private final Protocol.Control.KeyStatus.Builder keyStatus = Protocol.Control.KeyStatus.newBuilder();

    private final Timer timer = new Timer();

    private int width;
    private int height;

    private final TimerTask task = new TimerTask() {
        @Override
        public void run() {
            handleNetworkEvent();
        }
    };

    @Inject
    private Controller(MessageSender sender) {
        this.sender = sender;

        keyStatus.setKeyLeft(false);
        keyStatus.setKeyRight(false);
        keyStatus.setKeyUp(false);
        keyStatus.setKeyDown(false);
        keyStatus.setKeyAttack1(false);
        keyStatus.setKeyAttack2(false);

        control.setAngle(0);
        control.setWeapon(Protocol.Weapon.Pistol);

        timer.schedule(task, 0, 100);
    }

    private synchronized void handleNetworkEvent() {
        control.setKeyStatus(keyStatus);
        sender.sendControl(control);
    }

    private void setKeyState(int code, boolean state) {
        switch (code) {
            case KeyEvent.VK_LEFT:
            case KeyEvent.VK_A:
                keyStatus.setKeyLeft(state);
                handleNetworkEvent();
                break;
            case KeyEvent.VK_RIGHT:
            case KeyEvent.VK_D:
                keyStatus.setKeyRight(state);
                handleNetworkEvent();
                break;
            case KeyEvent.VK_UP:
            case KeyEvent.VK_W:
                keyStatus.setKeyUp(state);
                handleNetworkEvent();
                break;
            case KeyEvent.VK_DOWN:
            case KeyEvent.VK_S:
                keyStatus.setKeyDown(state);
                handleNetworkEvent();
                break;
            case KeyEvent.VK_1:
                control.setWeapon(Protocol.Weapon.Pistol);
                break;
            case KeyEvent.VK_2:
                control.setWeapon(Protocol.Weapon.Machinegun);
                break;
            case KeyEvent.VK_3:
                control.setWeapon(Protocol.Weapon.Shotgun);
                break;
        }
    }

    private void setMouseState(int code, boolean state) {
        switch (code) {
            case MouseEvent.BUTTON1:
                keyStatus.setKeyAttack1(state);
                handleNetworkEvent();
                break;
            case MouseEvent.BUTTON2:
                keyStatus.setKeyAttack2(state);
                handleNetworkEvent();
                break;
        }
    }

    @Override
    public void keyPressed(KeyEvent event) {
        if (!event.isAutoRepeat()) {
            setKeyState(event.getKeyCode(), true);
        }
    }

    @Override
    public void keyReleased(KeyEvent event) {
        if (!event.isAutoRepeat()) {
            setKeyState(event.getKeyCode(), false);
        }
    }

    @Override
    public void keyTyped(KeyEvent event) {
    }

    @Override
    public void mouseClicked(MouseEvent event) {
    }

    @Override
    public void mouseDragged(MouseEvent event) {
        updateAngle(event.getX(), event.getY());
    }

    @Override
    public void mouseEntered(MouseEvent event) {
    }

    @Override
    public void mouseExited(MouseEvent event) {
    }

    private void updateAngle(int x, int y) {
        final double centerX = x - width / 2;
        final double centerY = -y + height / 2;
        final double angle;
        if (centerX > 0) {
            angle = Math.atan(centerY / centerX);
        } else if (centerX < 0 && centerY > 0) {
            angle = Math.PI + Math.atan(centerY / centerX);
        } else if (centerX < 0 && centerY < 0) {
            angle = -Math.PI + Math.atan(centerY / centerX);
        } else if (centerX == 0 && centerY > 0) {
            angle = Math.PI / 2;
        } else {
            angle = -Math.PI / 2;
        }
        control.setAngle(angle);
    }

    @Override
    public void mouseMoved(MouseEvent event) {
    }

    @Override
    public void mousePressed(MouseEvent event) {
        updateAngle(event.getX(), event.getY());
        if (!event.isAutoRepeat()) {
            setMouseState(event.getButton(), true);
        }
    }

    @Override
    public void mouseReleased(MouseEvent event) {
        updateAngle(event.getX(), event.getY());
        if (!event.isAutoRepeat()) {
            setMouseState(event.getButton(), false);
        }
    }

    @Override
    public void mouseWheelMoved(MouseEvent event) {
    }

    @Override
    public void init(GLAutoDrawable drawable) {
    }

    @Override
    public void dispose(GLAutoDrawable drawable) {
    }

    @Override
    public void display(GLAutoDrawable drawable) {
    }

    @Override
    public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
        this.width = width;
        this.height = height;
    }
}
