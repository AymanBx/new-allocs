#ifndef	OPERATIONS_H
#define	OPERATIONS_H

#include "rasterImage.h"


typedef enum{
        WEIRD_VALUE = -1,
        HIGHT_ONLY,
        HIGHT_VERBOSE,
        WIDTH_ONLY,
        WIDTH_VERBOSE,
        HIGHT_WIDTH,
        HIGHT_WIDTH_VERBOSE
} RequestedDemensions;


typedef enum{
        WEIRD_COLOR = -1,
        RED,
        GREEN,
        BLUE
} ColorChannel;

typedef enum{
        WEIRD_ROTATION = 0,
        LEFT = -1,
        LEFTLEFT = -2,
        RIGHT = +1,
        RIGHTRIGHT = +2,
} Rotation;

/**	A function that gets dimentions of a RasterImage and formats a string to output those 
 *  dimensions according to what was requested.
 *	@param	image	a pointer to RasterImage object.
 *  @param  valueRequested  an int that describes which dimension was requested.
 *	@return	 a properly initialized RasterImage storing the image read
 */
char* getDimensions(RasterImage* image, RequestedDemensions valueRequested);


void splitImage(RasterImage* inImage, RasterImage* outImage, ColorChannel color);


void cropImage(RasterImage* inImage, RasterImage* outImage, int x, int y);


void rotateImage(RasterImage* inImage, RasterImage* outImage, Rotation x);


#endif  //  OPERATIONS_H