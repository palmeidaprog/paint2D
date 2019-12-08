#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>


struct Vector3
{
    float x;
    float y;
    float z;

    // ctors
    Vector3() : x(0), y(0), z(0) {};
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

    // utils functions
    void        set(float x, float y, float z);
    float       length() const;                         //
    float       distance(const Vector3& vec) const;     // distance between two vectors
    float       angle(const Vector3& vec) const;        // angle between two vectors
    Vector3&    normalize();                            //
    float       dot(const Vector3& vec) const;          // dot product
    Vector3     cross(const Vector3& vec) const;        // cross product
    bool        equal(const Vector3& vec, float e) const; // compare with epsilon

    // operators
    Vector3     operator-() const;                      // unary operator (negate)
    Vector3     operator+(const Vector3& rhs) const;    // add rhs
    Vector3     operator-(const Vector3& rhs) const;    // subtract rhs
    Vector3&    operator+=(const Vector3& rhs);         // add rhs and update this object
    Vector3&    operator-=(const Vector3& rhs);         // subtract rhs and update this object
    Vector3     operator*(const float scale) const;     // scale
    Vector3     operator*(const Vector3& rhs) const;    // multiplay each element
    Vector3&    operator*=(const float scale);          // scale and update this object
    Vector3&    operator*=(const Vector3& rhs);         // product each element and update this object
    Vector3     operator/(const float scale) const;     // inverse scale
    Vector3&    operator/=(const float scale);          // scale and update this object
    bool        operator==(const Vector3& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const Vector3& rhs) const;   // exact compare, no epsilon
    bool        operator<(const Vector3& rhs) const;    // comparison for sort
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    friend Vector3 operator*(const float a, const Vector3 vec);
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);
};

inline Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::operator+(const Vector3& rhs) const {
    return Vector3(x+rhs.x, y+rhs.y, z+rhs.z);
}

inline Vector3 Vector3::operator-(const Vector3& rhs) const {
    return Vector3(x-rhs.x, y-rhs.y, z-rhs.z);
}

inline Vector3& Vector3::operator+=(const Vector3& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z; return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this;
}

inline Vector3 Vector3::operator*(const float a) const {
    return Vector3(x*a, y*a, z*a);
}

inline Vector3 Vector3::operator*(const Vector3& rhs) const {
    return Vector3(x*rhs.x, y*rhs.y, z*rhs.z);
}

inline Vector3& Vector3::operator*=(const float a) {
    x *= a; y *= a; z *= a; return *this;
}

inline Vector3& Vector3::operator*=(const Vector3& rhs) {
    x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this;
}

inline Vector3 Vector3::operator/(const float a) const {
    return Vector3(x/a, y/a, z/a);
}

inline Vector3& Vector3::operator/=(const float a) {
    x /= a; y /= a; z /= a; return *this;
}

inline bool Vector3::operator==(const Vector3& rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

inline bool Vector3::operator!=(const Vector3& rhs) const {
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}

inline bool Vector3::operator<(const Vector3& rhs) const {
    if(x < rhs.x) return true;
    if(x > rhs.x) return false;
    if(y < rhs.y) return true;
    if(y > rhs.y) return false;
    if(z < rhs.z) return true;
    if(z > rhs.z) return false;
    return false;
}

inline float Vector3::operator[](int index) const {
    return (&x)[index];
}

inline float& Vector3::operator[](int index) {
    return (&x)[index];
}

inline void Vector3::set(float x, float y, float z) {
    this->x = x; this->y = y; this->z = z;
}

inline float Vector3::length() const {
    return sqrtf(x*x + y*y + z*z);
}

inline float Vector3::distance(const Vector3& vec) const {
    return sqrtf((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y) + (vec.z-z)*(vec.z-z));
}

inline float Vector3::angle(const Vector3& vec) const {
    // return angle between [0, 180]
    float l1 = this->length();
    float l2 = vec.length();
    float d = this->dot(vec);
    float angle = acosf(d / (l1 * l2)) / 3.141592f * 180.0f;
    return angle;
}

inline Vector3& Vector3::normalize() {
    //@@const float EPSILON = 0.000001f;
    float xxyyzz = x*x + y*y + z*z;
    //@@if(xxyyzz < EPSILON)
    //@@    return *this; // do nothing if it is ~zero vector

    //float invLength = invSqrt(xxyyzz);
    float invLength = 1.0f / sqrtf(xxyyzz);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

inline float Vector3::dot(const Vector3& rhs) const {
    return (x*rhs.x + y*rhs.y + z*rhs.z);
}

inline Vector3 Vector3::cross(const Vector3& rhs) const {
    return Vector3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
}

inline bool Vector3::equal(const Vector3& rhs, float epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon && fabs(z - rhs.z) < epsilon;
}

inline Vector3 operator*(const float a, const Vector3 vec) {
    return Vector3(a*vec.x, a*vec.y, a*vec.z);
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}


#endif // VECTOR3_H
