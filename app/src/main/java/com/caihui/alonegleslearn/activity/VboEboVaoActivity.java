package com.caihui.alonegleslearn.activity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import com.caihui.alonegleslearn.GLEngine;
import com.caihui.alonegleslearn.R;

import java.nio.ByteBuffer;

public class VboEboVaoActivity extends GLActivity {


    @Override
    public int getRendererType() {
        return GLEngine.RENDERER_TYPE_VBO_EBO_VAO;
    }


    @Override
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
