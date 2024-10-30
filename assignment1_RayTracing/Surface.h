#pragma once
//#include "HitRecord.h"
#include "Ray.h"
#include "Color.h"
#include "HitRecord.h"
#include <vector>
#include <iostream>

static glm::vec3* normal = new glm::vec3{ 0.0f, 0.0f, 0.0f };

class Surface {
public:
	//HitRecord rec;
	Surface() {}
	//So that I can loop through a vector<object> and see if the ray hits, then apply shading and stuff
	std::vector<Surface*> surfaces;

	void addSurface(Surface* surface) {
		surfaces.push_back(surface);
	}

	Surface setSurface(Surface& surface) {
		return surface;
	}
	//when a surface is hit, if the tmin is smaller than current tmin in lit, update to new tmin
};

struct HitRecord { //contains data about surface intersection
	Surface surface;
	float t; //real t
	glm::vec3 normal;
	glm::vec3 hit_pt;
	HitRecord() {}

	void evaluateT(float t_) {
		this->t = t_;
	}

	HitRecord(Surface surface, float t, glm::vec3 normal) {
		this->surface = surface;
		this->t = t;
		this->normal = normal;
	}

	void SetSurface(Surface surface) {
		this->surface = surface;
	}
};

class Sphere : public Surface {
	//a = ray origin
	//b = ray direction
	//r  = radius
	//t = hit distance
public:
	Sphere() {}
	std::string name;
	float radius;
	glm::vec3 center; 
	Color color;
	glm::vec3 normal;
	HitRecord record;
	float t;
	float normalX, normalY, normalZ;


	//Sphere(const float& radius, glm::vec3& center, Color& color);
	Sphere(const float radius, glm::vec3& center) {
		this->radius = radius;
		this->center = center;

	}
	void setColor(int r, int g, int b) {
		this->color.r = r;
		this->color.g = g;
		this->color.b = b;
	}

	void setRecord(int t, glm::vec3 normal, glm::vec3 hitPt) {
		this->record.t = t;
		this->record.normal = normal;
		this->record.hit_pt = hitPt;
		
	}

	Sphere CreateSphere(const float& radius, glm::vec3& center, Color& color);

	const bool Intersect(Ray& ray, Sphere sphere, glm::vec3 *vec) {
		HitRecord rec;
		//calc quadratic: At^2 + Bt + C = 0.
		//discriminant: b^2-4ac
		//-disc = no intersection, +disc = ray enters and exits sphere, disc,0 = touches @ 1 pt (grazes) 
		//check disc first
		//if smaller is in interval = first hit, else larger in interval is first hit, else no hit
		//normal @ pt P is n=2(p-c). unit normal is (p-c)R
		//R = radius
		float discriminant;
		//forloop that check if ray runs thorugh sphere, checking all pts in ray (change z)
		//a^2 + b^2 + c^2 -r^2 = 0
		//normal = 
		for (int i = 0; i < 2000; i++) {
			glm::vec3 ray_pt = glm::vec3(ray.origin.x, ray.origin.y, ray.origin.z + i);
			float deviation = (sphere.center.x - ray_pt.x) * (sphere.center.x - ray_pt.x) + (sphere.center.y - ray_pt.y) * (sphere.center.y - ray_pt.y) + (sphere.center.z - ray_pt.z) * (sphere.center.z - ray_pt.z) - (sphere.radius) * (sphere.radius); //intersection of sphere
			if (deviation <= 0) {
				//HitRecord rec;
				//intersection pt
				//2a+2b+2c-2r
				//normal.x = 2(raypt.x)
				//normal.y = 2(raypt.y)
				//normal.z = 2(raypt.z)
				//normal = center - raypt/radius
				//rec.normal = set face normal(ray, normal)
				float normalX = 2 * ray_pt.x;
				//if dot(ray.direction
				float x = 2;
				float y = 1;
				float z = 1;
				glm::vec3 tempNormal = glm::vec3((2*ray_pt.x), (2 * ray_pt.y), (2*ray_pt.z));

				float temp = 1 / (sqrt(tempNormal.x * tempNormal.x + tempNormal.y * tempNormal.y + tempNormal.z * tempNormal.z));
				//glm::vec3 dervative = glm::vec3 ((2 * x), (2*y), (2*z));
				//glm::vec3 temp = glm::vec3(dervative.x, dervative.y, dervative.z);
				//glm::vec3 n = temp dervative.length();
				
				//this->normal = temp * (tempNormal);
				vec = new glm::vec3 {( temp * (tempNormal)).x, (temp * (tempNormal)).y, (temp* (tempNormal)).z};
				//normal = temp * tempNormal;
				//this->normal[0] = normal_[0];
				//this->normal[1] = normal_[1];
				//this->normal[2] = normal_[2];
				//glm::vec3 normal_ = temp * (tempNormal);
				this->record.hit_pt = ray_pt;
				this->normalX = (temp * (tempNormal)).x;
				this->normalY = (temp * (tempNormal)).y;
				this->normalZ = (temp * (tempNormal)).z;
				this->t = i;
				this->record.evaluateT(i);

				
				
				//record.normal = normal;
				//record.surface = this;
				//save raypt in hitrecord
				return true;
			}
		}
		return false;

		
	}
};

class Plane : public Surface {
	glm::vec3 point;
	float radius;

};

class Triangle : public Surface {

};


