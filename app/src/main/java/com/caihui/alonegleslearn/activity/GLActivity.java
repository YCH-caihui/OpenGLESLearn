package com.caihui.alonegleslearn.activity;

import android.opengl.GLSurfaceView;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.caihui.alonegleslearn.GLEngine;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public abstract   class GLActivity extends AppCompatActivity implements GLSurfaceView.Renderer {

    public GLEngine mEngine;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        GLSurfaceView surfaceView = new GLSurfaceView(this);
        surfaceView.setEGLContextClientVersion(3);

        mEngine = new GLEngine();
        mEngine.nativeInit(getRendererType());
        surfaceView.setRenderer(this);
        setContentView(surfaceView);
    }


    public void setImageData(int format, int width, int height, byte[] bytes) {
        mEngine.setNativeImage(format, width, height, bytes);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        mEngine.onSurfaceCreate();
        initResource();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mEngine.onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        mEngine.onDrawFrame();
    }


    protected void initResource() {}
    public abstract int getRendererType();
}
