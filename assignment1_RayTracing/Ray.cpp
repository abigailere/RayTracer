#include "Ray.h"

Ray::Ray(glm::vec3 o, glm::vec3 d) {
	this->origin = o;
	this->direction = d;
}

glm::vec3 Ray::GetOrigin() {
	return origin;
}

glm::vec3 Ray::GetDirection() {
	return direction;
}

glm::vec3 Ray::EvaluateT(float t) {
	return origin + (t * direction);
}