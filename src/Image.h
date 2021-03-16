#include <stdint.h>
#include <cstdio>

#define STEG_HEADER_SIZE sizeof(uint32_t) * 8

enum ImageType {
	PNG, JPG, BMP, TGA
	//Image file type enumeration for deciding to which image type we are using
};

struct Image {
	uint8_t* data = NULL;
	//one dimension array that contain pixels
	size_t size = 0;
	//image size
	int w;
	//width (px)
	int h;
	//height (px)
	int channels;
	//channel numbers (like r, g, b, a or grayscale)

	Image(const char* filename);
	//construct image using reading a file
	Image(int w, int h, int channels);
	//construct image with creating empty array
	Image(const Image& img);
	//copy constructor
	~Image();
	//destructor

	bool read(const char* filename);
	//read image file and load to array
	bool write(const char* filename);
	//write image object to an image file

	int getWidth();
	//returns images's width
	int getHeight();
	//returns image's height
	ImageType get_file_type(const char* filename);
	//returns image extension

	Image& grayscaleAvg();
	//convert image to grayscale using average method
	Image& grayscaleLig();
	//convert image to grayscale using lightness method
	Image& grayscaleLum();
	//convert image to grayscale using lumination method
	void copyResized(Image *image);
	//copy image that send to function and resize it
};
