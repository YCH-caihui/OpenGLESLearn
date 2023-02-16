package com.caihui.alonegleslearn;


import android.graphics.Bitmap;

public class GLEngine {

    public static final int RENDERER_TYPE_HELLO_TRIANGLE = 100;
    public static final int RENDERER_TYPE_UBO = 101;
    public static final int RENDERER_TYPE_TEXTURE_MAP = 102;
    public static final int RENDERER_TYPE_YUV_MAP = 103;
    public static final int RENDERER_TYPE_VBO_EBO_VAO = 104;
    public static final int RENDERER_TYPE_TRANSFORM_SAMPLE = 105;



    public static final int IMAGE_FORMAT_RGBA = 0x01;
    public static final int IMAGE_FORMAT_NV21 = 0x02;
    public static final int IMAGE_FORMAT_NV12 = 0x03;
    public static final int IMAGE_FORMAT_I420 = 0x04;
    public static final int IMAGE_FORMAT_YUYV = 0x05;
    public static final int IMAGE_FORMAT_GARY = 0x06;

    static {
        System.loadLibrary("GLEngine-lib");
    }


    public GLEngine(){

    }




    public native void nativeInit(int renderType);
    public native void onSurfaceCreate();

    public native void updateParameter(int paramType, Object paramObj);

    public native void onSurfaceChanged(int width, int height);
    public native void onDrawFrame();



}
