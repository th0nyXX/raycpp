#include "Vec3.h"
#include <cmath>

Vec3::Vec3() : Vec3(0.0, 0.0, 0.0) {}

Vec3::Vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

Vec3::Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}

Vec3::Vec3(const Vec3 & v1, const Vec3 & v2): x(v2.x - v1.x), y(v2.y - v1.y), z(v2.z - v1.z){}


Vec3 Vec3::operator*(const float a) const { return Vec3(a*x, a*y, a*z); }
Vec3 Vec3::operator/(const float a) const { return Vec3(x/a, y/a, z/a); }
float Vec3::operator*(const Vec3& v) const { return x*v.x + y*v.y + z*v.z; }

Vec3 Vec3::operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }

Vec3 Vec3::operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
/**
*\fn Vec3 Vec3::operator-()
*\brief unary opposite operator for vector
*/
Vec3 Vec3::operator-() const{
	return Vec3(-this->x,-this->y, -this->z);
}

Vec3 Vec3::operator^(const Vec3& v) const { return Vec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x); }

float Vec3::length() const { return sqrtf(x*x + y*y + z*z); }

Vec3 Vec3::unit() const { float len = this->length(); return Vec3(x / len, y / len, z / len); }
