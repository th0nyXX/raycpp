#pragma once
#include "Vec3.h"
#include "Color.h"
#include "Image.h"

class Material{
public:
	Material();
	Material(float amb, float diff, float spec, float alpha, Color color);
	Material(float amb, float diff, float spec, float alpha, Color color, const char* file);
	const Vec3 get_color() { return color; };
	float get_phong_ambiant() { return phong_ambiant_factor; };
	float get_phong_diffuse() { return phong_diffuse_factor; };
	float get_phong_specular() { return phong_specular_factor; };
	float get_phong_alpha() { return phong_specular_alpha; };
private:
	float phong_ambiant_factor, phong_diffuse_factor, phong_specular_factor, phong_specular_alpha ;
	Color color;
	Image bump_map;
};