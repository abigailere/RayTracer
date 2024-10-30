
//#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
Camera::Camera(glm::vec3 u_, glm::vec3 v_, glm::vec3 w_, glm::vec3 lookAt_, glm::vec3 center_) {
	this->u = u_;
	this->v = v_;
	this->w = w_;
	this->lookAt = lookAt_;
	this->center = center_;
}
*/

/*
OrthographicCamera::OrthographicCamera(glm::vec3 lookAt, glm::vec3 up, glm::vec3 right, glm::vec3 center, glm::vec3 direction, float width, float height) {
	this->center = center;
	this->direction = direction;
	this->lookAt = lookAt;
	this->up = up;
	this->right = right;
	this->height = height;
	this->width = width;
}

*/
//OrthographicCamera::OrthographicCamera(glm::vec3& origin, glm::vec3& target, glm::vec3& up_) : lookAt(origin), up(target), right(up_)  {

//}
//OrthographicCamera::OrthographicCamera(glm::vec3 origin, glm::vec3 target, glm::vec3 up, float fov, float aspect_ratio) {

	//calc stuff, ray input ray(direction, origin)
	// corigin = e
	//ray origin = e + uu + vv
	//ray dir = -w
	
	//this->center = origin;
	//this->w = target - origin;
	//up = glm::cross(this->w, this->u); 
	//this->u = glm::cross(this->w, up);
	//this->v = glm::cross(this->w, this->u);
	//this->lookAt = -this->w; //d = -w, ray dir
	
	//int height_ = glm::tan(fov);
	//this->height = (int)fov;

	//int width_ = height_ * aspect_ratio;
	//this->width = width_;

	
	/*
	height = glm::tan(fov);
	width = height * aspect_ratio;
	center = origin;
	lookAt = glm::normalize(origin - target); //normalize (get unit)
	right = glm::normalize( glm::cross(up, lookAt)); //normalized
	up = glm::cross(lookAt, right);
	*/
	
	//glm::vec3 ray_origin = this->origin + 
	//e = camera origin, 
	
//}

/*
Ray OrthographicCamera::CreateRay() {
	glm::vec3 res1 = this->u * (float)this->width;
	glm::vec3 res2 = (float)this->height * this->v;
	glm::vec3 ray_origin = this->center + res1 + (float)this->height * this->v;
	return Ray(ray_origin, -lookAt);
}

Ray OrthographicCamera::GetRay(int i, int j) {
	//l = left, r = right, b = bttm, t = top
	auto viewport_center = this->center - this->lookAt;
//	auto vp_lowerleft = this->center - this->lookAt - (0.5f * lookAt * this->right) - 
	return Ray();
}

*/
