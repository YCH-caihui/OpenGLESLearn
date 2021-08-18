package com.caihui.alonegleslearn;


public class GLEngine {

    public static final int RENDERER_TYPE_HELLO_TRIANGLE = 100;

    static {
        System.loadLibrary("GLEngine-lib");
    }


    public GLEngine(){

    }


    public native void nativeInit(int renderType);
    public native void onSurfaceCreate();
    public native void onSurfaceChanged(int width, int height);
    public native void onDrawFrame();



}
