/**
* \author Marie DARRIGOL & Anthony LEONARD & Oph�lie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \class collision.h
* \brief Algorithm naif of collision
*/
#pragma once
#include "Ray.h"
#include "Scene.h"

	/**
	 * Determine the best scene objet collide
	 * return : impact point and the best scene object collide
	 * if not object was collide return ray's origin and nullptr
	**/
	pair<Vec3, SceneObject*> collide(Ray &ray, vector<SceneObject*>& sceneObjects);
	pair<Vec3, SceneObject*> collide(Ray &ray, Scene &scene);
	bool is_collisionned(Ray &ray, vector<SceneObject*>& sceneObjects);