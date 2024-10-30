#include "HitRecord.h"
HitRecord::HitRecord(Surface surface, float t, glm::vec3 normal) {
	this->surface = surface;
	this->t = t;
	this->normal = normal;
}

void HitRecord::SetSurface(Surface surface) {
	this->surface = surface;
}