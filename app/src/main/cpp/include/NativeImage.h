//
// Created by Ych-caihui on 2022/2/18.
//

#ifndef ALONEGLESLEARN_NATIVEIMAGE_H
#define ALONEGLESLEARN_NATIVEIMAGE_H

#include <stdio.h>

//Y Y Y Y Y Y
//Y Y Y Y Y Y
//Y Y Y Y Y Y
//Y Y Y Y Y Y
//U U U U U U                  Y U Y V Y U Y V Y U Y V
//U U U U U U                  Y U Y V Y U Y V Y U Y V
//V V V V V V                  Y U Y V Y U Y V Y U Y V
//V V V V V V                  Y U Y V Y U Y V Y U Y V
//- Planar -                          - Packed

//Y Y Y Y Y Y      Y Y Y Y Y Y      Y Y Y Y Y Y      Y Y Y Y Y Y   Y U Y V Y U Y V Y U Y V
//Y Y Y Y Y Y      Y Y Y Y Y Y      Y Y Y Y Y Y      Y Y Y Y Y Y   Y U Y V Y U Y V Y U Y V
//Y Y Y Y Y Y      Y Y Y Y Y Y      Y Y Y Y Y Y      Y Y Y Y Y Y   Y U Y V Y U Y V Y U Y V
//Y Y Y Y Y Y      Y Y Y Y Y Y      Y Y Y Y Y Y      Y Y Y Y Y Y   Y U Y V Y U Y V Y U Y V
//U U U U U U      V V V V V V      U V U V U V      V U V U V U   Y U Y V Y U Y V Y U Y V
//V V V V V V      U U U U U U      U V U V U V      V U V U V U   Y U Y V Y U Y V Y U Y V
//- I420 -          - YV12 -         - NV12 -         - NV21 -           -YUYV-


#define IMAGE_FORMAT_RGBA 0x01
#define IMAGE_FORMAT_NV21 0x02
#define IMAGE_FORMAT_NV12 0x03
#define IMAGE_FORMAT_I420 0x04
#define IMAGE_FORMAT_YUYV 0x05
#define IMAGE_FORMAT_GRAY 0x06


#define IMAGE_FORMAT_RGBA_EXT  "RGBA32"
#define IMAGE_FORMAT_NV21_EXT   "NV21"
#define IMAGE_FORMAT_NV12_EXT   "NV12"
#define IMAGE_FORMAT_I420_EXT   "I420"
#define IMAGE_FORMAT_YUYV_EXT   "YUYV"
#define IMAGE_FORMAT_GRAY "GRAY"


struct NativeImage
{
    int width;
    int height;
    int format;
    uint8_t * plane[3];
};

class NativeImageUtil
{
public:
    static void allocPlanes(NativeImage * pImage)
    {
        if(pImage->width == 0 || pImage->height == 0) return;
        switch (pImage->format)
        {
            case  IMAGE_FORMAT_RGBA:
                pImage->plane[0] = static_cast<uint8_t *>(malloc(pImage->width * pImage->height * 4));
                break;
        }
    }
};

#endif //ALONEGLESLEARN_NATIVEIMAGE_H
