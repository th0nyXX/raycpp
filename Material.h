/**
* \author Marie DARRIGOL & Anthony LEONARD & Oph�lie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \file material.h
* \brief represent a material associated with a sceneObject
*/

#pragma once
#include "Vec3.h"
#include "Color.h"
#include "Image.h"

class Material{
public:
	Material();
	Material(float ref_index);
	Material(float amb, float diff, float spec, float alpha, Color color);
	Material(float amb, float diff, float spec, float alpha, Color color, float refr);
	Material(float amb, float diff, float spec, float alpha, Color color, const char* file);
	inline const Vec3 get_color() { return color; };
	inline float get_phong_ambiant() { return phong_ambiant_factor; };
	inline float get_phong_diffuse() { return phong_diffuse_factor; };
	inline float get_phong_specular() { return phong_specular_factor; };
	inline float get_phong_alpha() { return phong_specular_alpha; };
	inline bool is_transparent() { return refractive_index >= 1; };
	inline float get_refractive_index() { return refractive_index; };

	// Functions regarding the bump map
	inline bool has_bump_map() const { return bump_map.isDefined(); }
	inline Color get_pixel_at(unsigned int i) const { return bump_map[i]; }
	inline unsigned int get_bump_map_width() const { return bump_map.getWidth(); }
	inline unsigned int get_bump_map_height() const { return bump_map.getHeight(); }

private:
	float phong_ambiant_factor, phong_diffuse_factor, phong_specular_factor, phong_specular_alpha ;///< phong model factors
	Color color; ///< material color
	Image bump_map;///< virtual texture map
	float refractive_index; ///< for transparent materials 
};