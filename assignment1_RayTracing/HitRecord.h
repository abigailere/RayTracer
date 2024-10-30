#pragma once
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Surface.h"
#include "Ray.h"
/*
struct HitRecord { //contains data about surface intersection
	Surface surface;
	float t; //real t
	glm::vec3 normal;

	HitRecord() {}
	HitRecord(Surface surface, float t, glm::vec3 normal) {
		this->surface = surface;
		this->t = t;
		this->normal = normal;
	}

	void SetSurface(Surface surface) {
		this->surface = surface;
	}
};
*/

