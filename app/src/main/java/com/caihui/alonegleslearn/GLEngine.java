package com.caihui.alonegleslearn;


import android.graphics.Bitmap;

public class GLEngine {

    public static final int RENDERER_TYPE_HELLO_TRIANGLE = 100;
    public static final int RENDERER_TYPE_UBO = 101;
    public static final int RENDERER_TYPE_TEXTURE_MAP = 102;
    public static final int RENDERER_TYPE_YUV_MAP = 103;

    static {
        System.loadLibrary("GLEngine-lib");
    }


    public GLEngine(){

    }


    public native void nativeInit(int renderType);
    public native void onSurfaceCreate();
    public native void setBitmapToNative(Bitmap bitmap);
    public native void onSurfaceChanged(int width, int height);
    public native void onDrawFrame();



}
