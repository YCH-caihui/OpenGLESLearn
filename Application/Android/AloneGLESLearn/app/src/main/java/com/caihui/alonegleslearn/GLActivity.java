package com.caihui.alonegleslearn;

import android.opengl.GLSurfaceView;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLActivity extends AppCompatActivity {

    private GLSurfaceView mSurfaceView;
    private GLEngine mEngine;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mSurfaceView = new GLSurfaceView(this);
        mSurfaceView.setEGLContextClientVersion(3);

        mEngine = new GLEngine();


        mSurfaceView.setRenderer(new GLSurfaceView.Renderer() {
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
        });
        setContentView(mSurfaceView);


    }


}
