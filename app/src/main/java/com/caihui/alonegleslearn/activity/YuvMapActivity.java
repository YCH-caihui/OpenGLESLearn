package com.caihui.alonegleslearn.activity;

import com.caihui.alonegleslearn.GLEngine;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class YuvMapActivity extends GLActivity {


    @Override
    protected void initResource() {
        super.initResource();
        try {
            InputStream inputStream = getAssets().open("YUV_Image_840x1074.NV21");
            byte[] buffer = new byte[inputStream.available()];
           int len = inputStream.read(buffer);
           if(len >= 0) {
               setImageData(GLEngine.IMAGE_FORMAT_NV21, 840, 1074, buffer);
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