﻿#pragma once
#include <vector>
#include <numeric>

using namespace std;

class Vec3 {
private:
	float x, y, z;
public:
	Vec3();
	Vec3(const float x, const float y, const float z);
	Vec3(const Vec3& v);

	float scalar_product(Vec3 &other);

	Vec3 operator*(const float a) const;
	float operator*(const Vec3& v) const;

	Vec3 operator+(const Vec3& v) const;

	Vec3 operator-(const Vec3& v) const;

	Vec3 operator^(const Vec3& v) const;

	float length() const;

	Vec3 unit() const;

	inline float getX() const { return x; };
	inline float getY() const { return y; };
	inline float getZ() const { return z; };
};

inline Vec3 operator*(const float k, const Vec3& v) { return v*k; }
