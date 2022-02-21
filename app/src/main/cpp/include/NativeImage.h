//
// Created by Ych-caihui on 2022/2/18.
//

#ifndef ALONEGLESLEARN_NATIVEIMAGE_H
#define ALONEGLESLEARN_NATIVEIMAGE_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "stdio.h"
#include "sys/stat.h"
#include "stdint.h"

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
#define IMAGE_FORMAT_GRAY_EXT   "GRAY"


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
    static void allocNativeImage(NativeImage * pImage)
    {
        if(pImage->width == 0 || pImage->height == 0) return;
        switch (pImage->format)
        {
            case  IMAGE_FORMAT_RGBA:
                pImage->plane[0] = static_cast<uint8_t *>(malloc(pImage->width * pImage->height * 4));
                break;
            case IMAGE_FORMAT_YUYV:
                pImage->plane[0] = static_cast<uint8_t *>(malloc(pImage->width * pImage->height  * 2));
                break;
            case IMAGE_FORMAT_NV12:
            case IMAGE_FORMAT_NV21:
                pImage->plane[0] = static_cast<uint8_t *>(malloc(pImage->width * pImage->height * 1.5));
                pImage->plane[1] = pImage->plane[0] + pImage->width * pImage->height;
                break;
            case IMAGE_FORMAT_I420:
                pImage->plane[0] = static_cast<uint8_t *>(malloc(pImage->width * pImage->height * 1.5));
                pImage->plane[1] = pImage->plane[0] + pImage->width * pImage->height;
                pImage->plane[2] = pImage->plane[1] + pImage->width * (pImage->height >> 2);
                break;
            case IMAGE_FORMAT_GRAY:
                pImage->plane[0] = static_cast<uint8_t *>(malloc(pImage->width * pImage->height));
                break;
        }
    }

    static void reduction(NativeImage * pImage)
    {
        if(pImage->width == 0 || pImage->height == 0) return;
        switch (pImage->format)
        {
            case IMAGE_FORMAT_NV12:
            case IMAGE_FORMAT_NV21:
                pImage->plane[1] = pImage->plane[0] + pImage->width * pImage->height;
                break;
            case IMAGE_FORMAT_I420:
                pImage->plane[0] = static_cast<uint8_t *>(malloc(pImage->width * pImage->height * 1.5));
                pImage->plane[1] = pImage->plane[0] + pImage->width * pImage->height;
                pImage->plane[2] = pImage->plane[1] + pImage->width * (pImage->height >> 2);
                break;
        }
    }

    static void freeNativeImage(NativeImage * pImage)
    {
        if(pImage == nullptr || pImage->plane[0] == nullptr) return;
        free(pImage->plane[0]);
        pImage->plane[0] = nullptr;
        pImage->plane[1] = nullptr;
        pImage->plane[2] = nullptr;
    }

    static void copyNativeImage(NativeImage * pSrcImg, NativeImage * pDstImg)
    {
        if(pSrcImg == nullptr || pSrcImg->plane[0] == nullptr) return;
        if(pSrcImg->format != pDstImg->format || pSrcImg->width != pDstImg->width || pSrcImg->height != pDstImg->height) return;

        if(pDstImg->plane[0] == nullptr) allocNativeImage(pDstImg);

        switch (pSrcImg->format)
        {
            case IMAGE_FORMAT_I420:
            case IMAGE_FORMAT_NV21:
            case IMAGE_FORMAT_NV12:
            {
                memcpy(pDstImg->plane[0], pSrcImg->plane[0], pSrcImg->width * pSrcImg->height * 1.5);
            }
                break;
            case IMAGE_FORMAT_YUYV:
            {
                memcpy(pDstImg->plane[0], pSrcImg->plane[0], pSrcImg->width * pSrcImg->height * 2);
            }
                break;
            case IMAGE_FORMAT_RGBA:
            {
                memcpy(pDstImg->plane[0], pSrcImg->plane[0], pSrcImg->width * pSrcImg->height * 4);
            }
                break;
            case IMAGE_FORMAT_GRAY:
            {
                memcpy(pDstImg->plane[0], pSrcImg->plane[0], pSrcImg->width * pSrcImg->height);
            }
                break;
            default:
            {
            }
                break;
        }

    }

    static void DumpNativeImage(NativeImage *pSrcImg, const char *pPath, const char *pFileName)
    {
        if (pSrcImg == nullptr || pPath == nullptr || pFileName == nullptr) return;

        if(access(pPath, 0) == -1)
        {
            mkdir(pPath, 0666);
        }

        char imgPath[256] = {0};
        const char *pExt = nullptr;
        switch (pSrcImg->format)
        {
            case IMAGE_FORMAT_I420:
                pExt = IMAGE_FORMAT_I420_EXT;
                break;
            case IMAGE_FORMAT_NV12:
                pExt = IMAGE_FORMAT_NV12_EXT;
                break;
            case IMAGE_FORMAT_NV21:
                pExt = IMAGE_FORMAT_NV21_EXT;
                break;
            case IMAGE_FORMAT_RGBA:
                pExt = IMAGE_FORMAT_RGBA_EXT;
                break;
            case IMAGE_FORMAT_YUYV:
                pExt = IMAGE_FORMAT_YUYV_EXT;
                break;
            case IMAGE_FORMAT_GRAY:
                pExt = IMAGE_FORMAT_GRAY_EXT;
                break;
            default:
                pExt = "Default";
                break;
        }

        sprintf(imgPath, "%s/IMG_%dx%d_%s.%s", pPath, pSrcImg->width, pSrcImg->height, pFileName, pExt);

        FILE *fp = fopen(imgPath, "wb");

        if(fp)
        {
            switch (pSrcImg->format)
            {
                case IMAGE_FORMAT_I420:
                {
                    fwrite(pSrcImg->plane[0],
                           static_cast<size_t>(pSrcImg->width * pSrcImg->height), 1, fp);
                    fwrite(pSrcImg->plane[1],
                           static_cast<size_t>((pSrcImg->width >> 1) * (pSrcImg->height >> 1)), 1, fp);
                    fwrite(pSrcImg->plane[2],
                           static_cast<size_t>((pSrcImg->width >> 1) * (pSrcImg->height >> 1)),1,fp);
                    break;
                }
                case IMAGE_FORMAT_NV21:
                case IMAGE_FORMAT_NV12:
                {
                    fwrite(pSrcImg->plane[0],
                           static_cast<size_t>(pSrcImg->width * pSrcImg->height), 1, fp);
                    fwrite(pSrcImg->plane[1],
                           static_cast<size_t>(pSrcImg->width * (pSrcImg->height >> 1)), 1, fp);
                    break;
                }
                case IMAGE_FORMAT_RGBA:
                {
                    fwrite(pSrcImg->plane[0],
                           static_cast<size_t>(pSrcImg->width * pSrcImg->height * 4), 1, fp);
                    break;
                }
                case IMAGE_FORMAT_YUYV:
                {
                    fwrite(pSrcImg->plane[0],
                           static_cast<size_t>(pSrcImg->width * pSrcImg->height * 2), 1, fp);
                    break;
                }
                default:
                {
                    fwrite(pSrcImg->plane[0],
                           static_cast<size_t>(pSrcImg->width * pSrcImg->height), 1, fp);
                    //LOGCATE("DumpNativeImage default");
                    break;
                }
            }

            fclose(fp);
            fp = NULL;
        }


    }
};

#endif //ALONEGLESLEARN_NATIVEIMAGE_H
