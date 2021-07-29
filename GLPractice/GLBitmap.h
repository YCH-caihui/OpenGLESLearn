#pragma once

#include <stdlib.h>

const static int COLOR_FORMAT_RGB24 = 1;

class GLBitmap 
{

private:
	int mWidth;
	int mHeight;
	int mFormat;
	char* mPixels;

public:
	GLBitmap(int width, int height, int format, char * pixels):mWidth(width),mHeight(height),mFormat(format),mPixels(pixels)
	{
	}

	inline int getWidth() 
	{
		return mWidth;
	}

	inline int getHeight()
	{
		return mHeight;
	}

	inline int getFormat()
	{
		return mFormat;
	}

	inline char* getPixels()
	{
		return mPixels;
	}


	~GLBitmap() 
	{
		if (mPixels != nullptr) {
			free(mPixels);
			mPixels = nullptr;
		}
	}


};