/**
* \author Marie DARRIGOL & Anthony LEONARD & Oph�lie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \file Camera.cpp
* \brief Camera representation in the scene 
*/

#include "Camera.h"
/*
 * On construit une cam�ra � partir d'une position et d'un vecteur permettant de positionner la frame
 * par rapport � l'observateur. On g�n�re une matrice de rotation � partir de ces informations.
 */
Camera::Camera(const Vec3& pOrigin, const Vec3& vFrame, const unsigned int picWidth, const unsigned int picHeight) : pOrigin(pOrigin), picWidth(picWidth), picHeight(picHeight) {
	Vec3 i(1.0f, 0.0f, 0.0f);
	Vec3 k = (i ^ vFrame).unit();
	Mat3 K({ { 0.0f, -k.getZ(), k.getY() }, { k.getZ(), 0.0f, -k.getX() }, { -k.getY(), k.getX(), 0.0f } }),
		K2 = K*K;
	float cos_th = i*vFrame.unit();
	float sin_th = (i^vFrame).length()/vFrame.length();
	R = I3 + sin_th*K + (1.0f - cos_th)*K2;

	distToFrame = vFrame.length();
	if (picWidth > picHeight) {
		width = 1.0f;
		height = ((float)picHeight) / ((float)picWidth);
	}
	else {
		height = 1.0f;
		width = ((float)picWidth) / ((float)picHeight);
	}
}

/*
* Retourne le rayon correspondant � un pixel donn� suivant les caract�ristiques de la camera.
*/
Ray Camera::getRay(const unsigned int x, const unsigned int y) const {
	float dy = (float)(picHeight - y);
	dy /= (float)picHeight;
	dy *= height;
	dy -= (height / 2.0f);

	float dz = (float)(picWidth - x);
	dz /= (float)picWidth;
	dz *= width;
	dz -= (width / 2.0f);

	Vec3 v1(distToFrame, dy, dz);
	Vec3 v2 = R*v1;

	return Ray(pOrigin, v2.unit(), RAY_TTL);
}