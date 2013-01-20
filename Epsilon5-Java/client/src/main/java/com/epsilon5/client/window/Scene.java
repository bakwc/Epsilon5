package com.epsilon5.client.window;

import com.google.inject.Inject;
import com.jogamp.opengl.util.GLArrayDataServer;
import com.jogamp.opengl.util.PMVMatrix;
import com.jogamp.opengl.util.glsl.ShaderCode;
import com.jogamp.opengl.util.glsl.ShaderProgram;
import com.jogamp.opengl.util.glsl.ShaderState;
import com.jogamp.opengl.util.texture.Texture;
import com.jogamp.opengl.util.texture.TextureIO;
import com.epsilon5.client.network.Protocol;
import com.epsilon5.client.world.CurrentWorld;
import com.epsilon5.client.world.Drawable;
import com.epsilon5.client.world.Sprite;
import com.epsilon5.client.world.Sprites;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.media.opengl.*;
import java.io.*;
import java.util.Map;
import java.util.TreeMap;

class Scene implements GLEventListener {

    private static final boolean CHECK_DRAWING_SEQUENCE = true;
    private static final boolean GL_DEBUGGING = false;

    private final Logger logger = LoggerFactory.getLogger(Scene.class);

    private final CurrentWorld currentWorld;

    private final PMVMatrix matrix = new PMVMatrix();

    private final Map<Integer, Sprite> sprites = new TreeMap<>();
    private final Map<Integer, Texture> textures = new TreeMap<>();

    private ShaderState shader;
    private GLUniformData uniformData;

    private GLArrayDataServer vertexBuffer;
    private GLArrayDataServer texCoordBuffer;
    private GLArrayDataServer elementsBuffer;

    private int lastLayer;

    private static final float[] VERTEX_BUFFER = {
            1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
    };

    private static final float[] TEXCOORD_BUFFER = {
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
    };

    private static final short[] ELEMENTS_BUFFER = {
            0, 1, 2,
            2, 1, 3,
    };

    @Inject
    private Scene(Sprites sprites, CurrentWorld currentWorld) {
        for (Sprite sprite : sprites.getSprite()) {
            this.sprites.put(sprite.getId(), sprite);
        }
        this.currentWorld = currentWorld;
    }

    private void draw(GL2ES2 gl, Drawable drawable) {
        final Sprite sprite = sprites.get(drawable.getSpriteId());
        final Texture texture = textures.get(drawable.getSpriteId());
        texture.bind(gl);

        final int paddingRight = sprite.getPaddingRight() == null ? 0 : sprite.getPaddingRight();
        final int paddingBottom = sprite.getPaddingBottom() == null ? 0 : sprite.getPaddingBottom();

        if (CHECK_DRAWING_SEQUENCE) {
            if (lastLayer >= drawable.getLayer()) {
                lastLayer = drawable.getLayer();
            } else {
                throw new IllegalStateException();
            }
        }

        matrix.glPushMatrix();
        matrix.glTranslatef(
                drawable.getX() - (sprite.getWidth() - paddingRight) / 2,
                drawable.getY() - (sprite.getHeight() - paddingBottom) / 2,
                0);
        matrix.glScalef(sprite.getWidth(), sprite.getHeight(), drawable.getLayer());
        shader.uniform(gl, uniformData);

        gl.glDrawElements(GL2ES2.GL_TRIANGLES,
                elementsBuffer.getComponentCount() * elementsBuffer.getElementCount(),
                elementsBuffer.getComponentType(), elementsBuffer.getVBOOffset());

        matrix.glPopMatrix();
    }

    private void drawScene(GL2ES2 gl) {
        final Protocol.Player hero = currentWorld.getHero();
        matrix.glTranslatef(-hero.getX(), -hero.getY(), 0);

        draw(gl, currentWorld.getBackgroundDrawable());

        for (int i = 0, count = currentWorld.getBulletCount(); i < count; ++i) {
            draw(gl, currentWorld.getBulletDrawable(i));
        }

        for (int i = 0, count = currentWorld.getPlayerCount(); i < count; ++i) {
            draw(gl, currentWorld.getPlayerDrawable(i));
        }
    }

    @Override
    public void display(GLAutoDrawable drawable) {
        final GL2ES2 gl = drawable.getGL().getGL2ES2();

        if (!currentWorld.isDrawable()) {
            gl.glClear(GL2ES2.GL_COLOR_BUFFER_BIT);
            return;
        }

        gl.glClear(GL2ES2.GL_DEPTH_BUFFER_BIT);

        {
            shader.useProgram(gl, true);
            matrix.glPushMatrix();

            elementsBuffer.bindBuffer(gl, true);
            vertexBuffer.bindBuffer(gl, true);
            texCoordBuffer.bindBuffer(gl, true);
        }

        if (CHECK_DRAWING_SEQUENCE) {
            lastLayer = Integer.MAX_VALUE;
        }

        drawScene(gl);

        {
            gl.glBindTexture(GL2ES2.GL_TEXTURE_2D, 0);

            shader.useProgram(gl, false);
            matrix.glPopMatrix();

            texCoordBuffer.bindBuffer(gl, false);
            vertexBuffer.bindBuffer(gl, false);
            elementsBuffer.bindBuffer(gl, false);
        }
    }

    @Override
    public void dispose(GLAutoDrawable drawable) {
        final GL2ES2 gl = drawable.getGL().getGL2ES2();

        for (Texture texture : textures.values()) {
            texture.destroy(gl);
        }

        shader.destroy(gl);
        matrix.destroy();
        vertexBuffer.destroy(gl);
        texCoordBuffer.destroy(gl);
        elementsBuffer.destroy(gl);
    }

    @Override
    public void init(GLAutoDrawable drawable) {
        if (GL_DEBUGGING) {
            final DebugGL2ES2 glDebug = new DebugGL2ES2(drawable.getGL().getGL2ES2());
            final TraceGL2ES2 glTrace = new TraceGL2ES2(glDebug, System.out);
            drawable.setGL(glTrace);
        }

        final GL2ES2 gl = drawable.getGL().getGL2ES2();

        gl.glEnable(GL2ES2.GL_BLEND);
        gl.glEnable(GL2ES2.GL_DEPTH_TEST);

        gl.glBlendFunc(GL2ES2.GL_SRC_ALPHA, GL2ES2.GL_ONE_MINUS_SRC_ALPHA);
        gl.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        gl.glTexParameteri(GL2ES2.GL_TEXTURE_2D, GL2ES2.GL_TEXTURE_MIN_FILTER, GL2ES2.GL_LINEAR_MIPMAP_LINEAR);
        gl.glTexParameteri(GL2ES2.GL_TEXTURE_2D, GL2ES2.GL_TEXTURE_MAG_FILTER, GL2ES2.GL_LINEAR);

        try {
            for (Sprite sprite : sprites.values()) {
                final File file = new File("textures/" + sprite.getTexture() + ".dds");
                textures.put(sprite.getId(), TextureIO.newTexture(file, false));
                logger.debug("Texture '{}' is loaded", sprite.getTexture());
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        final ShaderCode vs = ShaderCode.create(gl, GL2ES2.GL_VERTEX_SHADER,
                1, ShaderCode.class,
                new String[]{"shaders/scene.vert.txt"}, false);
        final ShaderCode fs = ShaderCode.create(gl, GL2ES2.GL_FRAGMENT_SHADER,
                1, ShaderCode.class,
                new String[]{"shaders/scene.frag.txt"}, false);

        final OutputStream baos = new ByteArrayOutputStream();
        final PrintStream stream = new PrintStream(baos);

        final ShaderProgram program = new ShaderProgram();
        boolean status;
        status = program.add(gl, vs, stream);
        status &= program.add(gl, fs, stream);
        status &= program.link(gl, stream);

        if (!status) {
            throw new RuntimeException(baos.toString());
        }

        shader = new ShaderState();
        shader.attachShaderProgram(gl, program, true);

        uniformData = new GLUniformData("mgl_PMVMatrix", 4, 4, matrix.glGetPMvMatrixf());
        shader.ownUniform(uniformData);

        vertexBuffer = GLArrayDataServer.createGLSL("mgl_Vertex", 3,
                GL2ES2.GL_FLOAT, false, 4, GL2ES2.GL_STATIC_DRAW);
        for (float e : VERTEX_BUFFER) vertexBuffer.putf(e);
        vertexBuffer.seal(gl, true);

        texCoordBuffer = GLArrayDataServer.createGLSL("mgl_MultiTexCoord", 2,
                GL2ES2.GL_FLOAT, false, 4, GL2ES2.GL_STATIC_DRAW);
        for (float e : TEXCOORD_BUFFER) texCoordBuffer.putf(e);
        texCoordBuffer.seal(gl, true);

        elementsBuffer = GLArrayDataServer.createData(3, GL2ES2.GL_UNSIGNED_SHORT, 2,
                GL2ES2.GL_STATIC_DRAW, GL2ES2.GL_ELEMENT_ARRAY_BUFFER);
        for (short e : ELEMENTS_BUFFER) elementsBuffer.puts(e);
        elementsBuffer.seal(gl, true);
    }

    @Override
    public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
        logger.info("Reshape ({}, {})", width, height);
        matrix.glMatrixMode(PMVMatrix.GL_PROJECTION);
        matrix.glLoadIdentity();
        matrix.glOrthof(width / -2, width / 2, height / -2, height / 2, 1, 10);
        matrix.glMatrixMode(PMVMatrix.GL_MODELVIEW);
        matrix.glLoadIdentity();
        matrix.glScalef(1, -1, -1);
    }

}
