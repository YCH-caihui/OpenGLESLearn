package com.caihui.alonegleslearn.activity;

import android.graphics.Bitmap;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.caihui.alonegleslearn.GLEngine;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public abstract class GLActivity extends AppCompatActivity {

    public GLEngine mEngine;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        GLSurfaceView surfaceView = new GLSurfaceView(this);
        surfaceView.setEGLContextClientVersion(3);

        mEngine = new GLEngine();

        mEngine.nativeInit(getRendererType());

        surfaceView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig config) {
                mEngine.onSurfaceCreate();
                Bitmap bitmap = getBitmap();
                if(bitmap != null) {
                    mEngine.setBitmapToNative(bitmap);
                }

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
        setContentView(surfaceView);


    }

    public abstract int getRendererType();

    protected Bitmap getBitmap() {
        return null;
    }

}
