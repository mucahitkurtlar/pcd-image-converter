#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define BYTE_BOUND(value) value < 0 ? 0 : (value > 255 ? 255 : value)
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"



Image::Image(const char* filename) {
	if(read(filename)) {
		printf("Read %s\n", filename);
		size = w*h*channels;
	}
	else {
		printf("Failed to read %s\n", filename);
	}
}

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
	size = w*h*channels;
	data = new uint8_t[size];
}

Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
	memcpy(data, img.data, size);
}

Image::~Image() {
	stbi_image_free(data);
}

bool Image::read(const char* filename) {
	data = stbi_load(filename, &w, &h, &channels, 0);
	return data != NULL;
}

bool Image::write(const char* filename) {
	ImageType type = get_file_type(filename);
	int success;
  switch (type) {
    case PNG:
      success = stbi_write_png(filename, w, h, channels, data, w*channels);
      break;
    case BMP:
      success = stbi_write_bmp(filename, w, h, channels, data);
      break;
    case JPG:
      success = stbi_write_jpg(filename, w, h, channels, data, 100);
      break;
    case TGA:
      success = stbi_write_tga(filename, w, h, channels, data);
      break;
  }
  return success != 0;
}
int Image::getWidth() {
	return w;
}
int Image::getHeight() {
	return h;
}
ImageType Image::get_file_type(const char* filename) {
	const char* ext = strrchr(filename, '.');
	if(ext != nullptr) {
		if(strcmp(ext, ".png") == 0) {
			return PNG;
		}
		else if(strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
			return JPG;
		}
		else if(strcmp(ext, ".bmp") == 0) {
			return BMP;
		}
		else if(strcmp(ext, ".tga") == 0) {
			return TGA;
		}
	}
	return PNG;
}
Image& Image::grayscaleAvg() {
	if (channels < 3) {
		std::cout << "The image has already been grayscaled" << std::endl;
		return *this;
	}
	for (int i = 0; i < size; i += channels) {
		int gray = (data[i] + data[i + 1] + data[i + 2]) / 3;
		memset(data + i, gray, 3);
	}

	return *this;
	
}
Image& Image::grayscaleLig() {
	if (channels < 3) {
		std::cout << "The image has already been grayscaled" << std::endl;
		return *this;
	}
	for (int i = 0; i < size; i += channels) {
		int gray = (std::max({data[i], data[i + 1], data[i + 2]}) + std::min({data[i], data[i + 1], data[i + 2]})) / 2;
		memset(data + i, gray, 3);
	}

	return *this;
}
Image& Image::grayscaleLum() {
	if (channels < 3) {
		std::cout << "The image has already been grayscaled" << std::endl;
		return *this;
	}
	for (int i = 0; i < size; i += channels) {
		int gray = 0.21 * data[i] + 0.72 * data[i + 1] + 0.07 * data[i + 3];
		memset(data + i, gray, 3);
	}

	return *this;
}
void Image::copyResized(Image *image) {
	stbir_resize_uint8(image->data, image->w, image->h, 0, data, w, h, 0, 3);

}