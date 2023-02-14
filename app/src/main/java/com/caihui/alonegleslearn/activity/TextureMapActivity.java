package com.caihui.alonegleslearn.activity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;

import com.caihui.alonegleslearn.GLEngine;
import com.caihui.alonegleslearn.R;

import java.nio.ByteBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class TextureMapActivity extends GLActivity{



    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        super.onSurfaceCreated(gl, config);
        initResource();
    }

    @Override
    public int getRendererType() {
        return GLEngine.RENDERER_TYPE_TEXTURE_MAP;
    }

    protected void initResource() {
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.a);
        if(bitmap != null) {
            int bytes = bitmap.getByteCount();
            ByteBuffer buf = ByteBuffer.allocate(bytes);
            bitmap.copyPixelsToBuffer(buf);
            byte[] byteArray = buf.array();
            setImageData(GLEngine.IMAGE_FORMAT_RGBA, bitmap.getWidth(), bitmap.getHeight(), byteArray);
        }
    }
}
