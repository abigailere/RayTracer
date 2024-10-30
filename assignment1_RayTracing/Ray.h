#pragma once
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Ray {
public:
	glm::vec3 origin;
	glm::vec3 direction;

	Ray();
	Ray(glm::vec3 o, glm::vec3 d) {
		this->origin = o;
		this->direction = d;
	}
	const glm::vec3 EvaluateT(float t) {
		return origin + (t * direction);
	}

	const glm::vec3 GetOrigin() {
		return this->origin;
	}
	const glm::vec3 GetDirection() {
		return this->direction;
	}
	glm::vec3 Getpt(float x) {
		glm::vec3 pt = this->origin + x * this->direction;
		//-x, y=0, +z
		return pt;
	}
};

