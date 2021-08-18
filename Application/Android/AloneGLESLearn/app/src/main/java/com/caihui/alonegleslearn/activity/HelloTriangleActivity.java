package com.caihui.alonegleslearn.activity;

import com.caihui.alonegleslearn.GLEngine;

public class HelloTriangleActivity extends GLActivity {

    @Override
    public int getRendererType() {
        return GLEngine.RENDERER_TYPE_HELLO_TRIANGLE;
    }
}
