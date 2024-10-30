#pragma once
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Ray.h"
class Camera
{
public:
	//~Camera() {}
	Ray CreateRay();
	//glm::vec3 u, v, w;
	//glm::vec3 lookAt;
	//glm::vec3 center;
	//glm::vec3 origin;
	//glm::vec3 direction;
	Camera() {}
	
};

class PerspectiveCamera : public Camera {
public:
	glm::vec3 lookAt;
	glm::vec3 up;
	glm::vec3 right; //d, u, v
	glm::vec3 center; //e
	//	glm::vec3 direction;
	int width, height;

	PerspectiveCamera(){}

	
	PerspectiveCamera(glm::vec3 origin, glm::vec3 target, glm::vec3 up, float fov, float aspect_ratio) {

		this->height = glm::tan(fov);
		this->width = height * aspect_ratio;

		this->center = origin;
		this->lookAt = glm::normalize(origin - target); //normalize (get unit)
		this->right = glm::normalize(glm::cross(up, this->lookAt)); //normalized
		this->up = glm::cross(this->lookAt, this->right);
	}
	Ray GetRay(int i, int j, int width, int height) {
		float u = (i - 256.0f + 0.5);
		float v = (j - 256.0f + 0.5);
		return Ray(this->center, glm::vec3(0, 0, 1));
	}
};


class OrthographicCamera : public Camera {
	//glm::vec3 u, v, w;
public:

	glm::vec3 lookAt;
	glm::vec3 up;
	glm::vec3 right; //d, u, v
	glm::vec3 center; //e
	int width, height;

	OrthographicCamera() {}

	OrthographicCamera(glm::vec3 origin, glm::vec3 target, glm::vec3 up, float fov, float aspect_ratio) {

		
		this->height = glm::tan(fov);
		this->width = height * aspect_ratio;

		this->center = origin;
		this->lookAt = glm::normalize(origin - target); //normalize (get unit)
		this->right = glm::normalize(glm::cross(up, this->lookAt)); //normalized
		this->up = glm::cross(this->lookAt, this->right);
		
	}

	Ray GetRay(int i, int j, int width, int height) {
		//l = left, r = right, b = bttm, t = top
		//auto viewport_center = this->center - this->lookAt;
		//u= left + (right - left)(i+0.5)/nx
		//v = bttm + (top-bttm)(j+0.5)/ny
		//glm::vec3 dir = lookAt + i * (float)this->width * right + j * (float)this->height * up;
		//	auto vp_lowerleft = this->center - this->lookAt - (0.5f * lookAt * this->right) - 
		//float u = i - width / 2;
		//float v = j - height / 2;
		float u = (i - 256.0f + 0.5);
		float v = (j-256.0f + 0.5);

	
		//glm::vec3 direction = this->lookAt + u * this->right + v * this->lookAt;
		//return Ray(center, glm::normalize(direction));
		return Ray(this->center, glm::vec3(0, 0, 1));
	}
};

//width height = nx, ny
//d + lookat = pixel plane center
//pixel plane matrix is a 2d vector, vecto of vectors. construct when running program
//the width and height is the width and height of the pixel plane
//the up and right are the same vectors for camera and pixel plane because its a parallel camera set up. the only thing changing is look at vector