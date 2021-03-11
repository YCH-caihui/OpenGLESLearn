package com.caihui.opengleslearn.view;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRootView extends GLSurfaceView {

    static {
        System.loadLibrary("native-lib");
    }


    public GLRootView(Context context, int glType) {
        super(context);
        init(glType);
    }


    {
        setRenderer(new GLRender());
        setRenderMode(RENDERMODE_CONTINUOUSLY);
        setEGLContextClientVersion(3);
    }

    private class GLRender implements Renderer {

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            GLRootView.this.onSurfaceCreated();
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            GLRootView.this.onSurfaceChanged(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            GLRootView.this.onDrawFrame();
        }
    }


    private native  void init(int glType);

    private native void onSurfaceCreated();

    private native void onSurfaceChanged(int width, int height);

    private native void onDrawFrame();
}
