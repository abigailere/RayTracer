#pragma once
#include "Color.h"
#include "Ray.h"
#include "Surface.h"
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Light {
public:
    Light(){}
    Color illuminate(Ray ray);
    float DiffuseLight(Ray& ray, Sphere sphere, int t) {
        float res;
        glm::vec3 norm2 = glm::vec3{(sphere.normalX), (sphere.normalY) , (sphere.normalZ) };
        glm::vec3 calc = -1.0f * glm::normalize(ray.direction) * norm2;
        float sum = calc.x + calc.y + calc.z;
        if (sum <= 0) {
            sum = 0;
            return sum;
           
        }
        else if (sum >= 1) {
            sum = 1;
            return sum;
           
        }
        else {
          
           return sum * 0.55f;
        }
       
    }
    
    //-----diffuse------
  //vec3 sphere.normal= normalize((hitpt-center of circle) * 2) 
  //vec3 calc = -direction of light * sphere.noraml 
  //float ans = sum of calc
  //if ans <= 0
      //ans =0
      //return ans
  //if ans >= 1
      //ans =1
      // return ans
  //else return ans * k (k is any # <= 1 to set intesity of particular light - minimum)
    float SpecularLight(Ray& ray, Sphere sphere, int t) {
         glm::vec3 norm2 = glm::vec3{ (sphere.normalX), (sphere.normalY) , (sphere.normalZ) };
         glm::vec3 calc = -1.0f * glm::normalize(ray.direction) * norm2;

         float sum = 2 * glm::pow(calc.x + calc.y + calc.z, 2);
         float value = calc.x + calc.y + calc.z;
         glm::vec3 calc2 = glm::normalize((sum * norm2) + ray.direction);
           if (value < 0) {
             value = 0;
             return value;
         }
        

         //check if 0, raise to power, multiply by i, then multiply by ks
         //assignment 4: look up fow to draw pts and lines with glfw
         
         return value * 0.40f;
    }
    //-------specular light-------
   //vec3 sphere.normal= normalize((hitpt-center of circle) * 2) 
   //vec3 calc = -direction of light * sphere.noraml 
   //float ans = 2*sum of calc
   //calc2 = normalize((ans*normal) + direction of light)
   //value = sum of calc2
   //if value < 0
       //value =0
   //intensity = value*k (k is any # <= 1 to set intesity of particular light)
   //-----diffuse------
   //vec3 sphere.normal= normalize((hitpt-center of circle) * 2) 
   //vec3 calc = -direction of light * sphere.noraml 
   //float ans = sum of calc
   //if ans <= 0
       //ans =0
       //return ans
   //if ans >= 1
       //ans =1
       // return ans
   //else return ans * k (k is any # <= 1 to set intesity of particular light - minimum)
};

struct SpecularLight : public Light {
    float intensity;
    float Illuminate(Surface surface, Ray ray, Sphere sphere, HitRecord record) { //change to hitrecord when we figure it out
        float res;
        record.normal = glm::normalize(record.hit_pt - sphere.center * 2.0f);
      //  glm::vec3 calc1 = 
        return res;
    }
};
//normal should be length 1, (divide by its length)
//parallel origin-> set origin and direction, converging to pt set origin
   //need save pt that hits sphere
   // normal = derivative of equation
   //-------specular light-------
   //vec3 sphere.normal= normalize((hitpt-center of circle) * 2) 
   //vec3 calc = -direction of light * sphere.noraml 
   //float ans = 2*sum of calc
   //calc2 = normalize((ans*normal) + direction of light)
   //value = sum of calc2
   //if value < 0
       //value =0
   //intensity = value*k (k is any # <= 1 to set intesity of particular light)
   //-----diffuse------
   //vec3 sphere.normal= normalize((hitpt-center of circle) * 2) 
   //vec3 calc = -direction of light * sphere.noraml 
   //float ans = sum of calc
   //if ans <= 0
       //ans =0
       //return ans
   //if ans >= 1
       //ans =1
       // return ans
   //else return ans * k (k is any # <= 1 to set intesity of particular light - minimum)
   //-----ambient------
   // just use specific value - no formula needed