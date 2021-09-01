package com.caihui.alonegleslearn.activity;

import com.caihui.alonegleslearn.GLEngine;

public class TextureActivity extends GLActivity{

    @Override
    public int getRendererType() {
        return GLEngine.RENDERER_TYPE_TEXTURE;
    }
}
