#include "Ray.h"
#include "SceneObject.h"
#include "Scene.h"
#include "collision.h"
#include <algorithm>

Ray::Ray(Vec3 pOrigin, Vec3 vDir, int ttl) : origin(pOrigin), direction(vDir), ttl(ttl) {}


/**
*\fn Color Ray::phong_ambiant(Material &mat, Light &light)
*\brief phong's ambiant reflection of this Ray, according to the Material of the collided SceneObject
*		and its Lighting.
*\return a new Color giving the RGB color componants each range between 0.0f and 1.0f
*/
Color Ray::phong_ambiant(Material &mat, Scene & scene){
	Color ambiant_color = mat.get_color() * (mat.get_phong_ambiant() * lights.get_ambiant());
	ambiant_color.normalise();
	return ambiant_color;
}


/**
*\fn float lambertian(Vec3 &collision_point, Vec3 &normal, Light &light)
*\brief express the lambertian coefficient describing the self shadowing due to the inclination
	toward light of a point on a SceneObject
*\return a float representing this factor, 
*/
float lambertian(Vec3 &collision_point, Vec3 &normal, Vec3 &light_direction) {
	float lambert = normal * light_direction.unit();
	return (lambert > 0.0f) ? lambert : 0.0f;
}

/**
*\fn Color Ray::phong_diffuse(Vec3 &collision_point, Vec3 &norm, Material &mat, Light &light)
*\brief phong's diffuse reflection of this Ray, according to the normal vector of the collided SceneObject
*		and its Material.
*\return a new Color giving the RGB color componants each range between 0.0f and 1.0f
*/
Color Ray::phong_diffuse(Vec3 &collision_point, Vec3 & norm, Material & mat, Scene & scene) {
	Vec3 light_direction = Vec3(collision_point, light.getPosition()).unit();
	Color diffuse_color = Color();
	if (!is_collisionned(Ray(collision_point, light_direction, 0), *objVect)) {
		diffuse_color = Color(mat.get_color() * mat.get_phong_diffuse() * light.get_diffuse() * lambertian(collision_point, norm, light_direction));
		diffuse_color.normalise();
	}
	return diffuse_color;
}

/**
*\fn Color Ray::phong_specular(Vec3 &collision_point, Vec3 &norm, Material &mat, Light &light)
*\brief phong's specular reflection of this Ray, according to the normal vector of the collided SceneObject
*		and its Material.
*\return a new Color giving the RGB color componants each range between 0.0f and 1.0f
*/
Color Ray::phong_specular(Vec3 &collision_point, Vec3 & norm, Material & mat, Scene & scene) {
	Color specular_color = Color();
	Vec3 light_direction, reflected_light;
	for (int i = 0; i < scene.getLights()->size(); i++) {
		light_direction = Vec3(collision_point, scene.getLights()->at(i)->getPosition()).unit();
		
		if (!is_collisionned(Ray(collision_point, light_direction, 0), *(scene.getSceneObjects()))) {
			reflected_light = (-light_direction).reflect(norm);
			specular_color = Color(mat.get_color() * mat.get_phong_specular() * light.get_specular() *
				pow(max(reflected_light * this->direction, 0.0f),
					mat.get_phong_alpha())
			);
			
		}
	}
	return specular_color;
}


/*
*\fn Color Ray::(Vec3 &collision_point, Vec3 & norm, Material & mat, Scene & scene)
*\brief calculate the color of a ray pointing to a particular collision point, according to Phong's model shading.
*\return the RGB color resulting of the Phong shading
*/
Color Ray::phong_shading(Scene & scene)
{
	Color amb, dif, spe, composition;

	// collision detection
	pair<Vec3, SceneObject*> intersection = collide(*this, *(scene.getSceneObjects()));

	//if collision calculate shading
	if (intersection.second != nullptr) {
		Material mat = intersection.second->getMaterial();
		Vec3 collision_point = intersection.first, 
			 norm = intersection.second->computeBump(intersection.first);

		amb = phong_ambiant(mat, scene);
		dif = phong_diffuse(collision_point, norm, mat, scene);
		spe = phong_specular(collision_point, norm, mat, scene);
		
		if (this->ttl <= 0) {
			composition = (amb * (1.0f / 3.0f)) + (dif * (1.0f / 3.0f)) + (spe * (1.0f / 3.0f));
		} else {
			Ray reflection = Ray(collision_point, this->direction.reflect(norm) , this->ttl - 1);
			composition = (amb / 4.0f) + (dif / 4.0f) + (spe / 4.0f) + (reflection.phong_shading(scene) / 4.0f);
		}
	// if no collision show scene background color
	} else {
		composition = scene.getBackground();
	}
	composition.normalise();
	return composition;
}