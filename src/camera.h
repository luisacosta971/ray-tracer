#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"

class camera {
public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int    image_width  = 100;  // Rendered image width in pixel count

    void render(const hittable& world) {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for(int row = 0;row < image_height;row++) {
            std::clog << "\rScanlines remaining: " << (image_height-row) << ' ' << std::flush;
            for(int col = 0; col < image_width;col++) {
                auto pixel_center = pixel_00 + (col * pixel_delta_u) + (row * pixel_delta_v);
                auto ray_direction = pixel_center - center;
                ray r(center, ray_direction);

                color pixel_color = ray_color(r, world);
                write_color(std::cout, pixel_color);
            }
        }
        std::clog << "\rDone.                 \n";
    }

private:
    int    image_height;   // Rendered image height
    point3 center;         // Camera center
    point3 pixel_00;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below

    void initialize() {
        image_height = std::max(1, int(image_width / aspect_ratio));

        center = point3(0, 0, 0);

        // Viewport dimensions
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * double(image_width) / image_height;
        auto focal_length = 1.0;

        // Vectors for viewport edges. U for horizontal, v for vertical.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Delta from pixel to pixel in both directions
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Location of upper left corner and pixel
        auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel_00 = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(const ray& r, const hittable& world) {
        hit_record rec;
        if(world.hit(r, interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + color(1,1,1));
        }

        vec3 unit_direction = unit_vector(r.getDirection());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }

};

#endif