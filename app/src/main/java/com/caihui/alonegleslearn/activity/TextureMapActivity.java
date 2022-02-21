package com.caihui.alonegleslearn.activity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;

import com.caihui.alonegleslearn.GLEngine;
import com.caihui.alonegleslearn.R;

import java.nio.ByteBuffer;

public class TextureMapActivity extends GLActivity{


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }

    @Override
    public int getRendererType() {
        return GLEngine.RENDERER_TYPE_TEXTURE_MAP;
    }

    @Override
    protected void initSource() {
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
