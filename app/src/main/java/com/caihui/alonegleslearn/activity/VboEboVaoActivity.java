package com.caihui.alonegleslearn.activity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;

import com.caihui.alonegleslearn.GLEngine;
import com.caihui.alonegleslearn.R;

import java.nio.ByteBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class VboEboVaoActivity extends GLActivity {

    private static final int PARAM_TYPE_INIT_BITMAP = 0;


    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        super.onSurfaceCreated(gl, config);
        initResource();
    }

    @Override
    public int getRendererType() {
        return GLEngine.RENDERER_TYPE_VBO_EBO_VAO;
    }



    protected void initResource() {
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.a);
        if(bitmap != null) {
            updateParameter(PARAM_TYPE_INIT_BITMAP, bitmap);
        }


    }

}
