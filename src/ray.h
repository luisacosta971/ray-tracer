#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    explicit ray() = delete;
    explicit ray(const point3& orig, const vec3& dir) : origin(orig), direction(dir) {}

    const point3& getOrigin() const { return origin; }
    const vec3& getDirection() const { return direction; }

    point3 at(double scalar) {
        return origin + scalar * direction;
    }

private:
    point3 origin;
    vec3 direction;
};

#endif