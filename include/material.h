#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "vec3.h"
#include "ray.h"
#include "object.h"
#include "sphere.h"


class Material
{
	protected:
		color cor;
		float shininess;
		color specularColor;

	public:

		virtual ~Material() {}

		virtual bool scatter(const Ray & r_, const HitRecord & rec, vec3 & attenuation, Ray & scattered) const = 0;

		color getColor() {return this->cor;};
		float getShininess() {return this->shininess;};
		color getSpecularColor() {return this->specularColor;};

};


class Lambertian : public Material
{
	public:
		Lambertian(color c_, color sc_ = color(1,1,1), float s_ = 64) 
		{ this->cor = c_; this->specularColor = sc_; this->shininess = s_; }

		bool scatter(const Ray & r_, const HitRecord & rec, vec3 & attenuation, Ray & scattered) const
		{
			vec3 target = rec.p + rec.normal + random_in_unit_sphere();
			scattered = Ray(rec.p, target - rec.p);
			attenuation = cor;

			return true;
		};
};

class Metal : public Material
{
	public:
		Metal(color c_, color sc_ = color(1,1,1), float s_ = 64) 
		{ this->cor = c_; this->specularColor = sc_; this->shininess = s_; }

		bool scatter(const Ray & r_, const HitRecord & rec, vec3 & attenuation, Ray & scattered) const
		{
			vec3 reflected = reflect (unit_vector(r_.get_direction()),rec.normal);
			scattered = Ray(rec.p, reflected);
			attenuation = cor;

			return (dot(scattered.get_direction(), rec.normal) > 0);
		};
};



#endif