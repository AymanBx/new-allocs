/*----------------------------------------------------------------------------------+
|	This is a modified version of the so-called "Lighthouse Library" for reading	|
|	images encoded in the *uncompressed, uncommented .tga (TARGA file) format. 		|
|	I had been using and modifying this code for years, simply mentioning			|
|	"Source Unknown" in my comments when I finally discovered, thanks to Web		|
|	searches, the origin of this code.  By then it had been adapted to work along	|
|	with reader/writer code for another image file format: the awful PPM/PBM/PGM	|
|	format of obvious Unix origin.													|
|	This is just to say that I am not claiming authorship of this code.  I am only	|
|	distributing it in this form instead of the original because (1) I have long	|
|	lost the original code, and (2) This version works with images organized		|
|	nicely into a struct.															|
|																					|
|	Jean-Yves Hervé		Dept. of Computer Science and Statistics, URI				|
|						2018-05-02													|
+----------------------------------------------------------------------------------*/

#include <stdlib.h>        
#include <stdio.h>

#include "imageIO_TGA.h"

void swapRGB(unsigned char* theData, int height, int width);
void swapRGBA(unsigned char* theData, int height, int width);


//----------------------------------------------------------------------
//	Utility function for memory swapping
//	Used because TGA stores the RGB data in reverse order (BGR)
//----------------------------------------------------------------------
void swapRGB(unsigned char* theData, int height, int width)
{
	int			imgSize;
	unsigned char tmp;

	imgSize = height*width;

	for(int k = 0; k < imgSize; k++)
	{
		tmp = theData[k*3+2];
		theData[k*3+2] = theData[k*3];
		theData[k*3] = tmp;
	}
}

void swapRGBA(unsigned char* theData, int height, int width)
{
    int imgSize;
    unsigned char temp;
    
    imgSize = height*width;
    
    for(int k=0; k<imgSize; k++){
        temp = theData[k*4+2];
        theData[k*4+2] = theData[k*4];
        theData[k*4] = temp;
    }
}

// ---------------------------------------------------------------------
//	Function : readTGA 
//	Description :
//	
//	This function reads an image of type TGA (8 or 24 bits, uncompressed
//	
//----------------------------------------------------------------------

RasterImage readTGA(const char* filePath)
{
	RasterImage info;

	//--------------------------------
	//	open TARGA input file
	//--------------------------------
	FILE* tga_in = fopen(filePath, "rb" );
	if (tga_in == NULL)
	{
		printf("Cannot open image file %s\n", filePath);
		exit(11);
	}

	//--------------------------------
	//	Read the header (TARGA file)
	//--------------------------------
	char head[18] ;
	fread( head, sizeof(char), 18, tga_in ) ;
	/* Get the size of the image */
	info.width = (int)(((unsigned int)head[12]&0xFF) | (unsigned int)head[13]*256);
	info.height = (int)(((unsigned int)head[14]&0xFF) | (unsigned int)head[15]*256);
	int imgSize = info.height * info.width;

	unsigned char* data;
	if((head[2] == 2) && (head[16] == 24))
	{
		info.type = RGBA32_RASTER;
		info.bytesPerPixel = 4;
		info.bytesPerRow = 4*info.width;
		data = (unsigned char*) malloc(imgSize*4);
		
	}
	else if((head[2] == 3) && (head[16] == 8))
	{
		info.type = GRAY_RASTER;
		info.bytesPerPixel = 1;
		info.bytesPerRow = info.width;
		data = (unsigned char*) malloc(imgSize);
	}
	else
	{
		printf("Unsuported TGA image: ");
		printf("Its type is %d and it has %d bits per pixel.\n", head[2], head[16]);
		printf("The image must be uncompressed while having 8 or 24 bits per pixel.\n");
		fclose(tga_in);
		exit(12);
	}

	if(data == NULL)
	{
		printf("Unable to allocate memory\n");
		fclose(tga_in);
		exit(13);
	}
	info.raster = (void*) data;

	//--------------------------------
	//	Read the pixel data
	//--------------------------------

	//	Case of a color image
	//------------------------	
	//if (info.type == kTGA_COLOR) *****************************
	if(info.type == RGBA32_RASTER)
	{
		//	First check if the image is mirrored vertically (a bit setting in the header)
		if(!(head[17]&0x20))
		{
			for(int i = 0; i < info.height; i++)
			{
				unsigned char* rowPtr = data + (info.height-i-1)*info.bytesPerRow;
                for (int j=0; j<info.width; j++)
                {
                    fread(rowPtr, 3*sizeof(char), 1, tga_in);
                    rowPtr[3] = 0xFF;
					rowPtr += 4;
                }
			}
		}
		else
        {
            unsigned char* dest = data;
            for (int i=0; i<info.height; i++)
            {
                for (int j=0; j<info.width; j++)
                {
                    fread(dest, 3*sizeof(char), 1, tga_in);
                    dest+=4;
                }
            }
			
        }
        
        //  tga files store color information in the order B-G-R
        //  we need to swap the Red and Blue components
    	swapRGBA(data, info.height, info.width);
	}

	//	Case of a gray-level image
	//----------------------------	
	else
	{
		//	First check if the image is mirrored vertically (a bit setting in the header)
		if(head[17]&0x20)
		{
			unsigned char* ptr = data + imgSize - info.width;
			for(int i = 0; i < info.height; i++)
			{
				fread( ptr, sizeof(char), info.width, tga_in ) ;
				ptr -= info.width;
			}
		}
		else
			fread(data, sizeof(char), imgSize, tga_in);
	}

	fclose( tga_in) ;
	return info;
}	


//---------------------------------------------------------------------*
//	Function : writeTGA 
//	Description :
//	
//	 This function write out an image of type TGA (24-bit color)
//	
//	Return value: Error code (0 = no error)
//----------------------------------------------------------------------*/ 
int writeTGA(char* filePath, RasterImage* info)
{
	//--------------------------------
	// open TARGA output file 
	//--------------------------------
	FILE* tga_out = fopen(filePath, "wb" );
	if (tga_out == NULL)
	{
		printf("Cannot create image file %s \n", filePath);
		return 21;
	}

	//	Yes, I know that I tell you over and over that cascading if-else tests
	//	are bad style when testing an integral value, but here only two values
	//	are supported.  If I ever add one more I'll use a switch, I promise.
	
	//------------------------------
	//	Case of a color image
	//------------------------------
	if (info->type == RGBA32_RASTER)
	{
		//--------------------------------
		// create the header (TARGA file)
		//--------------------------------
		char	head[18] ;
		head[0]  = 0 ;		  					// ID field length.
		head[1]  = 0 ;		  					// Color map type.
		head[2]  = 2 ;		  					// Image type: true color, uncompressed.
		head[3]  = head[4] = 0 ;  				// First color map entry.
		head[5]  = head[6] = 0 ;  				// Color map lenght.
		head[7]  = 0 ;		  					// Color map entry size.
		head[8]  = head[9] = 0 ;  				// Image X origin.
		head[10] = head[11] = 0 ; 				// Image Y origin.
		head[13] = (char) (info->width >> 8) ;		// Image width.
		head[12] = (char) (info->width & 0x0FF) ;
		head[15] = (char) (info->height >> 8) ;		// Image height.
		head[14] = (char) (info->height & 0x0FF) ;
		head[16] = 24 ;		 					// Bits per pixel.
//		head[17] = 0 ;		  					// Image descriptor bits ;
		head[17] = 0x20 ;		  				// Image descriptor bits ;
		fwrite( head, sizeof(char), 18, tga_out );

		unsigned char* data  = (unsigned char*) info->raster;
		for(int i = 0; i < info->height; i++)
		{
			unsigned long offset = i*4*info->width;
			for(int j = 0; j < info->width; j++)
			{
				fwrite(&data[offset+2], sizeof(char), 1, tga_out);
				fwrite(&data[offset+1], sizeof(char), 1, tga_out);
				fwrite(&data[offset], sizeof(char), 1, tga_out);
				offset+=4;
			}
		}

		fclose( tga_out ) ;
	}
	//------------------------------
	//	Case of a gray-level image
	//------------------------------
	else if (info->type == GRAY_RASTER)
	{
		//--------------------------------
		// create the header (TARGA file)
		//--------------------------------
		char	head[18] ;
		head[0]  = 0 ;		  					// ID field length.
		head[1]  = 0 ;		  					// Color map type.
		head[2]  = 3 ;		  					// Image type: gray-level, uncompressed.
		head[3]  = head[4] = 0 ;  				// First color map entry.
		head[5]  = head[6] = 0 ;  				// Color map lenght.
		head[7]  = 0 ;		  					// Color map entry size.
		head[8]  = head[9] = 0 ;  				// Image X origin.
		head[10] = head[11] = 0 ; 				// Image Y origin.
		head[13] = (char) (info->width >> 8) ;		// Image width.
		head[12] = (char) (info->width & 0x0FF) ;
		head[15] = (char) (info->height >> 8) ;		// Image height.
		head[14] = (char) (info->height & 0x0FF) ;
		head[16] = 8 ;		 					// Bits per pixel.
		head[17] = 0 ;		  					// Image descriptor bits ;
		fwrite( head, sizeof(char), 18, tga_out );

		unsigned char* data  = (unsigned char*) info->raster;
		for(int i = 0; i < info->height; i++)
		{
			fwrite(&data[i*info->width], sizeof(char), info->width, tga_out);
		}

		fclose( tga_out ) ;
	}
	else
	{
		printf("Image type not supported for output\n");
		return 22;
	}
	


	return 0;
}	

