#include <stdio.h>
#include <stdlib.h>
//
#include "rasterImage.h"
#include "operations.h"

/**	A function that gets dimentions of a RasterImage and formats a string to output those 
 *  dimensions according to what was requested.
 *	@param	image	a pointer to RasterImage object.
 *  @param  valueRequested  an int that describes which dimension was requested.
 *	@return	 a properly initialized RasterImage storing the image read
 */
char* getDimensions(RasterImage* image, RequestedDemensions valueRequested){
    char* message = (char*)malloc(35);

    switch (valueRequested)
    {
    case HIGHT_ONLY:
        sprintf(message, "%d\n", image->height);
        break;
    
    case HIGHT_VERBOSE:
        sprintf(message, "Hight: %d\n", image->height);
        break;

    case WIDTH_ONLY:
        sprintf(message, "%d\n", image->width);
        break;

    case WIDTH_VERBOSE:
        sprintf(message, "Width: %d\n", image->width);
        break;

    case HIGHT_WIDTH:
        sprintf(message, "%d %d\n", image->width, image->height);
        break;

    case HIGHT_WIDTH_VERBOSE:
        sprintf(message, "Width: %d, Hight: %d\n", image->width, image->height);
        break;

    default:
        sprintf(message, "Something went terribly wrong!\n");
        break;
    }
    return message;
}


void splitImage(RasterImage* inImage, RasterImage* outImage, ColorChannel color){
    int* inRaster = (int*)(inImage->raster);
    int* outRaster = (int*)(outImage->raster);

    for (unsigned int i=0; i<inImage->height; i++)
		{
			for (unsigned int j=0; j<inImage->width; j++)
			{
				unsigned char* inRgba = (unsigned char*) (inRaster + i*inImage->width + j);
                unsigned char* outRgba = (unsigned char*) (outRaster + i*outImage->width + j);
                
				//	rgba[0] -> red, rgba[1] -> green, rgba[2] -> blue, rgba[3] -> alpha
				outRgba[color] = inRgba[color];
			}
		}

}


void cropImage(RasterImage* inImage, RasterImage* outImage, int x, int y){
    int* inRaster = (int*)(inImage->raster);
    int* outRaster = (int*)(outImage->raster);

    for (unsigned int i=0; i<inImage->height; i++)
		{
			for (unsigned int j=0; j<inImage->width; j++)
			{
                if (i >= y && j >= x){
                    if (i < (y + outImage->height - 1) && j < (x + outImage->width - 1)){
                        unsigned char* inRgba = (unsigned char*) (inRaster + i*inImage->width + j);
                        unsigned char* outRgba = (unsigned char*) (outRaster + (i-y)*outImage->width + (j-x));
				        
                        //	rgba[0] -> red, rgba[1] -> green, rgba[2] -> blue, rgba[3] -> alpha
                        outRgba[0] = inRgba[0];
                        outRgba[1] = inRgba[1];
                        outRgba[2] = inRgba[2];
                        outRgba[3] = inRgba[3];
                    }
                }
			}
		}

}


void rotateImage(RasterImage* inImage, RasterImage* outImage, Rotation x){
    int* inRaster = (int*)(inImage->raster);
    int* outRaster = (int*)(outImage->raster);
    int inHeight = inImage->height;
    int inWidth = inImage->width;
    // int outHeight = outImage->height;
    // int outWidth = outImage->width;

    for (unsigned int row=0; row<inHeight; row++)
		{
			for (unsigned int col=0; col<inWidth; col++)
			{
                unsigned char* inRgba = (unsigned char*) (inRaster + row*inWidth + col);
                unsigned char* outRgba;
                int new_r, new_c;
                switch (x)
                {
                case RIGHT:
                    new_r = col;
                    new_c = inHeight-row-1;
                    outRgba = (unsigned char*) (outRaster + new_r*inHeight + new_c);
                    break;


                case LEFTLEFT:
                case RIGHTRIGHT:
                    new_r = inHeight-row-1;
                    new_c = inWidth-col-1;
                    outRgba = (unsigned char*) (outRaster + new_r*inHeight + new_c);
                    break;

                case LEFT:
                    new_r = inWidth-col-1;
                    new_c = row;
                    outRgba = (unsigned char*) (outRaster + new_r*inHeight + new_c);
                    break;

                default:
                    printf("Something went terribly wrong. Rotation: %d", x);
                    exit(404);
                }
                outRgba[0] = inRgba[0];
                outRgba[1] = inRgba[1];
                outRgba[2] = inRgba[2];
                outRgba[3] = inRgba[3];
            }
        }
}