#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <memory>
//#include "vec3.h"
#include "ray.h"
#include "object.h"
//#include "sphere.h"
#include "texture.h"


class Material
{
	protected:
		color cor;
		float shininess;
		color specularColor;
		std::shared_ptr<Texture> texture;


	public:

		virtual ~Material() {}

		virtual bool scatter(const Ray & r_, const HitRecord & rec, vec3 & attenuation, Ray & scattered) const = 0;

		color getColor(const vec3 & p = vec3(), float u = 0, float v = 0) {return this->texture->value(p,u,v);};
		float getShininess() {return this->shininess;};
		color getSpecularColor() {return this->specularColor;};

		void setTexture(std::shared_ptr<Texture> t_) {this->texture = t_;};

};


class Lambertian : public Material
{
	public:
		Lambertian(color c_, color sc_ = color(1,1,1), float s_ = 64, std::shared_ptr<Texture> t_ = std::make_shared<Constant_texture>(color(0.3,0.3,0.3))) 
		{ this->cor = c_; this->specularColor = sc_; this->shininess = s_; this->texture = t_;}

		bool scatter(const Ray & r_, const HitRecord & rec, vec3 & attenuation, Ray & scattered) const
		{
			vec3 target = rec.p + rec.normal + random_in_unit_sphere();
			scattered = Ray(rec.p, target - rec.p);
			attenuation = this->texture->value(rec.p,rec.u,rec.v);

			return true;
		};
};

class Metal : public Material
{
	public:
		Metal(color c_, color sc_ = color(1,1,1), float s_ = 64, std::shared_ptr<Texture> t_ = std::make_shared<Constant_texture>(color(0.3,0.3,0.3))) 
		{ this->cor = c_; this->specularColor = sc_; this->shininess = s_; this->texture = t_;}

		bool scatter(const Ray & r_, const HitRecord & rec, vec3 & attenuation, Ray & scattered) const
		{
			vec3 reflected = reflect (unit_vector(r_.get_direction()),rec.normal);
			scattered = Ray(rec.p, reflected);
			attenuation = this->texture->value(rec.p,rec.u,rec.v);

			return (dot(scattered.get_direction(), rec.normal) > 0);
		};
};

class Dielectric : public Material
{
	private:
		float ref_idx;

	public:

		Dielectric(float ri) {ref_idx = ri;}

		bool scatter(const Ray & r_, const HitRecord & rec, vec3 & attenuation, Ray & scattered) const
		{
			vec3 outward_normal;
			vec3 reflected = reflect(r_.get_direction(), rec.normal);
			float ni_over_nt;

			attenuation = this->texture->value(rec.p,rec.u,rec.v);
			vec3 refracted;

			if (dot(r_.get_direction(), rec.normal) > 0)
			{
				outward_normal = -rec.normal;
				ni_over_nt = ref_idx;
			}
			else
			{
				outward_normal = rec.normal;
				ni_over_nt = 1.0/ref_idx;
			}

			if (refract(r_.get_direction(), outward_normal, ni_over_nt, refracted))
			{
				scattered = Ray(rec.p, refracted);
			}
			else
			{
				scattered = Ray(rec.p, reflected);
				return false;
			}

			return true;

		};
};

#endif