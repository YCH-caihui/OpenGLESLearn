package com.caihui.alonegleslearn.activity;

import com.caihui.alonegleslearn.GLEngine;

public class YuvMapActivity extends GLActivity {

    @Override
    public int getRendererType() {
        return GLEngine.RENDERER_TYPE_YUV_MAP;
    }
}
