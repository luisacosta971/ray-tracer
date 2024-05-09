#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include <algorithm>


color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.getDirection());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

    // Image

    const auto ASPECT_RATIO = 16.0 / 9.0;

    const int IMAGE_WIDTH = 400;
    const int IMAGE_HEIGHT = std::max(1, int(IMAGE_WIDTH / ASPECT_RATIO));

    // World

    hittable_list world;

    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * double(IMAGE_WIDTH) / IMAGE_HEIGHT;
    auto camera_center = point3(0, 0, 0);
    auto focal_length = 1.0;

    // Vectors for viewport edges. U for horizontal, v for vertical.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Delta from pixel to pixel in both directions
    auto pixel_delta_u = viewport_u / IMAGE_WIDTH;
    auto pixel_delta_v = viewport_v / IMAGE_HEIGHT;

    // Location of upper left corner and pixel
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel_00 = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for(int row = 0;row < IMAGE_HEIGHT;row++) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT-row) << ' ' << std::flush;
        for(int col = 0; col < IMAGE_WIDTH;col++) {
            auto pixel_center = pixel_00 + (col * pixel_delta_u) + (row * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
    return 0;
}