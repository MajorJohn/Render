#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "vec3.h"
#include <vector>
#include <algorithm>

using namespace std;

class Light
{
	protected:
		color cor;
		float intensity;
		vec3 light;

	public:
		virtual ~Light() {}

		virtual vec3 getNormal(point3 p_) = 0;

		virtual color getColor(point3 p_ = point3()) {return this->cor*this->intensity;};

		virtual bool shadow(HitRecord t_, float dist) = 0;

		virtual bool shadow(HitRecord t_) = 0;

		virtual bool getLights(vector<std::shared_ptr<Light>> & ls_) = 0;
		
		float getIntensity() {return intensity;};

};

class GlobalLight : public Light
{
	public:

		GlobalLight(vec3 l_, color c_ = color(1,1,1), float i_ = 1.0)
		{ this->light = l_; this->cor = c_; this->intensity = i_; }

		vec3 getNormal(point3 p_) {return this->light;};

		bool shadow(HitRecord t_, float dist) {return true;};
		bool shadow(HitRecord t_) {return false;};
		bool getLights(vector<std::shared_ptr<Light>> & ls_) {return true;}

};

class PointLight : public Light
{	
	public:
		PointLight(vec3 l_, color c_ = color(1,1,1), float i_ = 1.0)
		{ this->light = l_; this->cor = c_; this->intensity = i_; }

		vec3 getNormal(point3 p_) {return (this->light - p_);};

		bool shadow(HitRecord t_, float dist) 
		{if(distance(t_.p, light) < dist) return false;
		 return true;};
		bool shadow(HitRecord t_) {return false;};
		bool getLights(vector<std::shared_ptr<Light>> & ls_) {return true;}

};

class SpotLight : public Light
{
	private:
		vec3 dir;
		float angle;

	public:
		SpotLight(vec3 l_, color c_ = color(1,1,1), vec3 d_ = vec3 (0,-1,0), float a_ = -1, float i_ = 1.0)
		{ this->light = l_; this->cor = c_; dir = d_; dir.make_unit_vector();
		angle = a_; this->intensity = i_;}

		vec3 getNormal(point3 p_) {return (this->light - p_);};

		bool shadow(HitRecord t_, float dist) 
		{
			if(distance(t_.p, light) < dist)
			{
				vec3 ld =  light - t_.p;
				ld.make_unit_vector();
				if(dot(ld, -dir) > angle)
					return false;
			}
		 	return true;
		};

		bool shadow(HitRecord t_)
		{
			vec3 ld = light - t_.p;
			ld.make_unit_vector();
			if(dot(ld, -dir) > angle)
					return false;
			return true;
		};
		bool getLights(vector<std::shared_ptr<Light>> & ls_) {return true;}

};

class AreaLight : public Light
{	
	private:
		vec3 dir;
		float angle;
		int nl = 10;
		vector<std::shared_ptr<Light>> lights;
		std::shared_ptr<Object> object;

	public:
		AreaLight(vec3 l_, color c_ = color(1,1,1), vec3 d_ = vec3 (0,-1,0), float a_ = -1, float i_ = 1.0)
		{ 
			vec3 center;
			float intens = i_/((float)nl);
			for (int i = 0; i < nl; ++i)
			{
				center = (random_in_unit_sphere()/10) + l_;
				lights.push_back(std::make_shared<SpotLight>(center, c_, d_, a_, intens));
			}
		}

		bool getLights(vector<std::shared_ptr<Light>> & ls_)
		{
			for (int i = 0; i < lights.size(); ++i)
			{
				ls_.push_back(lights[i]);
			}

			return false;
		};

		vec3 getNormal(point3 p_) {return this->light;};

		bool shadow(HitRecord t_, float dist) {return true;};
		bool shadow(HitRecord t_) {return false;};

};


#endif