package com.caihui.alonegleslearn.activity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import com.caihui.alonegleslearn.GLEngine;
import com.caihui.alonegleslearn.R;

public class TextureMapActivity extends GLActivity{

    @Override
    public int getRendererType() {
        return GLEngine.RENDERER_TYPE_TEXTURE_MAP;
    }

    @Override
    protected Bitmap getBitmap() {
        return BitmapFactory.decodeResource(getResources(), R.drawable.a);
    }
}
