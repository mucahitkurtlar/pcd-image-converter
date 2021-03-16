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



	Image firstImage("lena.png");
    int imw = firstImage.getWidth();
    int imh = firstImage.getHeight();
    firstImage.grayscaleAvg();
    firstImage.write("grayAver.jpg");
    int selectedW = 84;
    int selectedH = 48;

    if (84 * imh / imw <= 48) {
        selectedH = 84 * imh / imw;
        std::cout << "Auto fixed for max width" << selectedW << "x" << selectedH << "px" <<  std::endl;
    } else if (48 * imw / imh <= 84) {
        selectedW = 48 * imw / imh;
        std::cout << "Auto fixed for max height " << selectedW << "x" << selectedH << "px" << std::endl;
    }
    Image resized(selectedW, selectedH, 3);
    resized.copyResized(&firstImage);
    resized.write("resized.jpg");

	return 0;
}