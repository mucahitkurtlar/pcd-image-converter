#include <iostream>
#include <cstring>
#include "Image.h"


int main(int argc, char** argv)
{
    if (argc > 1 && (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")))
    {
        std::cout << "Usage: pcdcon [file] [options] ...\n"
            "Options:\n"
            "\t--help\t\t-h\tPrint this message end exit\n"
            "\t--version\t-v\tPrint pcdcon version and exit\n"
            "\t--grayscale\t-g\tExport grayscale image\n"
            "\t--resized\t-r\tExport resized image\n";
        return 0;
    }
	Image test("dexter.jpeg");
    //test.write("copy.png");
    Image white = test;
    //for (int i = 0; i < white.w * white.channels; i++) {
    //    white.data[i] = 255;
    //}
    //white.write("white.png");
    //Image blank(100, 100, 3);
    //blank.write("blank.jpg");
    test.grayscale_lum();
    test.write("gray_lum.jpg");

    
	return 0;
}