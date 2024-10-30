#include "Surface.h"

void Surface::addSurface(Surface* surface) {
	surfaces.push_back(surface);

}

Surface Surface::setSurface(Surface& surface) {
	return surface;
}

Sphere::Sphere(const float radius, glm::vec3& center) {
	this->radius = radius;
	this->center = center;
}

bool Sphere::Intersect(Ray &ray, float t0, float t1) {
	//calc quadratic: At^2 + Bt + C = 0.
	//discriminant: b^2-4ac
		//-disc = no intersection, +disc = ray enters and exits sphere, disc,0 = touches @ 1 pt (grazes) 
	//check disc first
		//if smaller is in interval = first hit, else larger in interval is first hit, else no hit
	//normal @ pt P is n=2(p-c). unit normal is (p-c)R
	//R = radius
	float discriminant;
	
	//a = (d*d)
	auto A = ray.direction.length() * ray.direction.length(); //int
	
	
	//b = d(e-c)^2
	glm::vec3 temp = ray.origin - center;
	float B = glm::dot(temp, ray.direction); //vec3
	//c = (e-c)(e-c)-R^2
	auto C = temp.length() * temp.length() - radius * radius; //float

	discriminant = glm::dot(B, B) - (4 * A * C);
	//t = (-b + sqrt(discriminant))/a
	//t = (-b - sqrt(discriminant))/a
	float t_curr = 0;
	if (discriminant > 0) { //if intersection
		//calc equation
		t_curr = (-B + glm::sqrt(discriminant)) / (float)A;

		//check for intersection: larger
		if (t_curr < t1 && t_curr >t0) {//within interval, save contents to hit record
			/*HitRecord record;
			record.t = t_curr;
			//record.surface = this;
			//record.surface = Sphere::setSurface(this);
			glm::vec3 ray_pt = ray.EvaluateT(record.t); //may be t_curr
			//glm::vec3 outward_normal = (ray_pt - center) / radius;
			record.normal = (ray_pt - center) / radius;
			*/
			return true;
		}

		t_curr = (-B - glm::sqrt(discriminant)) / A;
		if (t_curr < t1 && t_curr >t0) {
			/*HitRecord record;
			record.t = t_curr;
			//record.surface = this;
			//record.surface = Sphere::setSurface(this);
			glm::vec3 ray_pt = ray.EvaluateT(record.t); //may be t_curr
			//glm::vec3 outward_normal = (ray_pt - center) / radius;
			record.normal = (ray_pt - center) / radius;
			*/
			return true;
		}
	}
	

	return false;

}

/*
HitRecord Surface::Hit(Ray r, double t0, double t1) {
	HitRecord record;
	//glm::vec3 
		//sphere
	//calc quadratic: At^2 + Bt + C = 0.
	//discriminant: b^2-4ac
		//-disc = no intersection, +disc = ray enters and exits sphere, disc,0 = touches @ 1 pt (grazes) 
	//check disc first
		//if smaller is in interval = first hit, else larger in interval is first hit, else no hit
	//normal @ pt P is n=2(p-c). unit normal is (p-c)R
	//R = radius
	float discriminant;
	float A, B, C;
	//a = (d*d)
	auto A = r.direction.length() * r.direction.length(); //int


	//b = d(e-c)^2
	glm::vec3 temp = r.origin - ;
	auto B = temp * ray.direction; //vec3, maybe direction.length
	//c = (e-c)(e-c)-R^2
	auto C = temp.length() * temp.length() - radius * radius;

	discriminant = (B * B) - (4 * A * C);
	//sqrt discriminant
   //t = (-b + sqrt(discriminant))/a
   //t = (-b - sqrt(discriminant))/a

	if (discriminant > 0) { //if intersection
		//calc equation
		float t_curr = (-B + glm::sqrt(discriminant)) / A;

		//check for intersection: larger
		if (t_curr < t1 && t_curr >t0) {//within interval, save contents to hit record
			HitRecord record;
			record.t = t_curr;
			record.surface = this;

		}
		float t_curr = (-B - glm::sqrt(discriminant)) / A;
		if (t_curr < t1 && t_curr >t0) {

		}
	}
	return record;
	
}
*/