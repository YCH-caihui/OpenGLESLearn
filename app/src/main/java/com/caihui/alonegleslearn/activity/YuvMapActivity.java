package com.caihui.alonegleslearn.activity;

import android.os.Bundle;

import com.caihui.alonegleslearn.GLEngine;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class YuvMapActivity extends GLActivity {


    private static final int PARAM_TYPE_INIT_YUV = 0;

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        super.onSurfaceCreated(gl, config);
        initResource();
    }

    protected void initResource() {
        try {
            InputStream inputStream = getAssets().open("YUV_Image_840x1074.NV21");
            byte[] buffer = new byte[inputStream.available()];
           int len = inputStream.read(buffer);
           if(len >= 0) {
              // setImageData(GLEngine.IMAGE_FORMAT_NV21, 840, 1074, buffer);
               updateParameter(PARAM_TYPE_INIT_YUV, new YUVParam(GLEngine.IMAGE_FORMAT_NV21, 840, 1074, buffer));
           }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public int getRendererType() {
        return GLEngine.RENDERER_TYPE_YUV_MAP;
    }
}

class YUVParam {

    int format;
    int width;
    int height;
    byte[] yuvData;

    YUVParam(int format, int width, int height, byte[] yuvData) {
        this.format = format;
        this.width = width;
        this.height = height;
        this.yuvData = yuvData;
    }
}
