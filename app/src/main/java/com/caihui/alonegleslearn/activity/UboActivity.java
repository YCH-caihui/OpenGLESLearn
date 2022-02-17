package com.caihui.alonegleslearn.activity;

import com.caihui.alonegleslearn.GLEngine;

public class UboActivity extends GLActivity {

    @Override
    public int getRendererType() {
        return GLEngine.RENDERER_TYPE_UBO;
    }
}
