#ifndef BMP_LOAD
#define BMP_LOAD

#include <string>
#include <vector>
#include "vertex.h"

using namespace std;

/*
    Taken from http://www.gamedev.net/topic/287626-loading-bitmaps-for-textures-using-glut/
*/
#pragma pack(push, 1)
// taken from  http://msdn.microsoft.com/en-us/library/aa930622.aspx
typedef struct tagBITMAPINFOHEADER {
  u_int32_t biSize;
  int32_t biWidth;
  int32_t biHeight;
  u_int16_t biPlanes;
  u_int16_t biBitCount;
  u_int32_t biCompression;
  u_int32_t biSizeImage;
  int32_t biXPelsPerMeter;
  int32_t biYPelsPerMeter;
  u_int32_t biClrUsed;
  u_int32_t biClrImportant;
} BITMAPINFOHEADER;


//taken from http://msdn.microsoft.com/en-us/library/aa930979.aspx
typedef struct tagBITMAPFILEHEADER {
  u_int16_t  bfType;
  u_int32_t  bfSize;
  u_int16_t  bfReserved1;
  u_int16_t  bfReserved2;
  u_int32_t  bfOffBits;
} BITMAPFILEHEADER;

#pragma pack(pop)
// taken and adapted  from ttp://www.gamedev.net/topic/287626-loading-bitmaps-for-textures-using-glut/


vector<int>  loadTextures(vector<string> files);



#endif // SHAPE_H
