#include "bmpload.h"
#include <assert.h>
#include <fstream>


struct Image
{
    Image():data(0){}
    ~Image(){
        delete [] data;
    }
    u_int32_t sizeX;
    u_int32_t sizeY;
    char *data;
};

int ImageLoad(const char *filename, Image *image);

vector<int>  loadTextures(vector<string> files)
{
    vector<int> rv;

    int *textures = new int[files.size()];

    glGenTextures(files.size(), (GLuint*)textures);

    for(int i=0;i<files.size();++i)
    {
        string file = files[i];
        Image* pim = new Image();
        if(ImageLoad(file.c_str(), pim))
        {
            glBindTexture(GL_TEXTURE_2D, *(textures+i));
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); /* scale linearly when image bigger than texture*/
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); /* scale linearly when image smalled than texture*/
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, pim->sizeX, pim->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pim->data);
        }
        delete pim;
        rv.push_back(*(textures+i));
    }
    return rv;
}



static unsigned int getint(FILE *fp)
{
    int c, c1, c2, c3;

    /* get 4 bytes*/
    c = getc(fp);
    c1 = getc(fp);
    c2 = getc(fp);
    c3 = getc(fp);

    return ((unsigned int) c) +
           (((unsigned int) c1) << 8) +
           (((unsigned int) c2) << 16) +
           (((unsigned int) c3) << 24);
}

static unsigned int getshort(FILE *fp)
{
    int c, c1;

    /*get 2 bytes*/
    c = getc(fp);
    c1 = getc(fp);

    return ((unsigned int) c) + (((unsigned int) c1) << 8);

}


/* quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  */
/* See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.*/

int ImageLoad(const char *filename, Image *image)
{
    FILE *file;
    u_int32_t size;                 /* size of the image in bytes.*/
    u_int32_t i;                    /* standard counter.*/
    u_int16_t planes;          /* number of planes in image (must be 1) */
    u_int16_t bpp;             /* number of bits per pixel (must be 24)*/
    char temp;                          /* temporary color storage for bgr-rgb conversion.*/

    /* make sure the file is there.*/
    if ((file = fopen(filename, "rb"))==NULL)
    {
        printf("File Not Found : %s\n",filename);
        return 0;
    }

    /* seek through the bmp header, up to the width/height:*/
    fseek(file, 18, SEEK_CUR);

    /* No 100% errorchecking anymore!!!*/

    /* read the width*/
    image->sizeX = getint (file);
    printf("Width of %s: %lu\n", filename, image->sizeX);

    /* read the height */
    image->sizeY = getint (file);
    printf("Height of %s: %lu\n", filename, image->sizeY);

    /* calculate the size (assuming 24 bits or 3 bytes per pixel).*/
    size = image->sizeX * image->sizeY * 3;

    /* read the planes*/
    planes = getshort(file);
    if (planes != 1)
    {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }

    /* read the bpp*/
    bpp = getshort(file);
    if (bpp != 24)
    {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }

    /* seek past the rest of the bitmap header.*/
    fseek(file, 24, SEEK_CUR);

    /* read the data. */
    image->data = new char[size];
    if (image->data == NULL)
    {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }

    if ((i = fread(image->data, size, 1, file)) != 1)
    {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }

    for (i=0; i<size; i+=3) /* reverse all of the colors. (bgr -> rgb)*/
    {
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;
    }

    /* we're done.*/
    return 1;
}

