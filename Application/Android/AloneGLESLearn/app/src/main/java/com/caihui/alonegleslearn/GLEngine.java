package com.caihui.alonegleslearn;

import javax.microedition.khronos.opengles.GL10;

public class GLEngine {

    static {
        System.loadLibrary("GLEngine-lib");
    }


    public GLEngine(){

    }


    public native void onSurfaceCreate();
    public native void onSurfaceChanged(int width, int height);
    public native void onDrawFrame();



}
