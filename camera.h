#ifndef CAMERA_H
#define CAMERA_H

#include <vector3.h>

class Camera
{
    int x1, y1, z1, x2, y2, z2;
    double distance, pov;
    float fov;

public:
    Camera() noexcept;
    virtual ~Camera();

    inline Vector3 getEye() {
        return Vector3(this->x1, this->y1, this->z1);
    }

    inline Vector3 getTarget() {
        return Vector3(this->x2, this->y2, this->z2);
    }

    inline Vector3 getUpDir() {
        return Vector3(0, 1, 0);
    }

    inline double getPOV() const noexcept {
        return this->pov;
    }

    inline void setPOV(double pov) {
        this->pov = pov;
    }

    inline void setDistance(double distance) {
        this->distance = distance;
    }

    inline double getDistance() const noexcept{
        return this->distance;
    }

    inline void addToFOV(float add) {
        this->fov += add;
    }

    inline float getFOV() const noexcept {
        return this->fov;
    }

    inline void setX1(int x) noexcept {
        this->x1 = x;
    }

    inline void setX2(int x) noexcept {
        this->x2 = x;
    }

    inline void setY1(int y) noexcept {
        this->y1 = y;
    }

    inline void setY2(int y) noexcept {
        this->y2 = y;
    }

    inline void setZ1(int z) noexcept {
        this->z1 = z;
    }

    inline void setZ2(int z) noexcept {
        this->z2 = z;
    }

    inline int getX1() const noexcept {
        return this->x1;
    }

    inline int getX2() const noexcept {
        return this->x2;
    }

    inline int getY1() const noexcept {
        return this->y1;
    }

    inline int getY2() const noexcept {
        return this->y2;
    }

    inline int getZ1() const noexcept {
        return this->z1;
    }

    inline int getZ2() const noexcept {
        return this->z2;
    }
};

#endif
