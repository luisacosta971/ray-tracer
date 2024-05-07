#include "vec3.h"
#include "color.h"

#include <iostream>

int main() {
    const int IMAGE_HEIGHT = 256;
    const int IMAGE_WIDTH = 256;

    /*
    P3
    IMAGE_WIDTH IMAGE_HEIGHT
    255
    */
    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for(int row = 0;row < IMAGE_HEIGHT;row++) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT-row) << ' ' << std::flush;
        for(int col = 0; col < IMAGE_WIDTH;col++) {
            color current_pixel(double(col)/(IMAGE_WIDTH-1), double(row)/(IMAGE_HEIGHT-1), 0.0);
            write_color(std::cout, current_pixel);
        }
    }
    std::clog << "\rDone.                 \n";
    return 0;
}