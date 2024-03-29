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



    public void updateParameter(int paramType, Object paramObj) {
        mEngine.updateParameter(paramType,paramObj);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        mEngine.onSurfaceCreate();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mEngine.onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        mEngine.onDrawFrame();
    }


    public abstract int getRendererType();
}
