#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "vec3.h"

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

		float getIntensity() {return intensity;};
};

class GlobalLight : public Light
{
	public:

		GlobalLight(vec3 l_, color c_ = color(1,1,1), float i_ = 1.0)
		{ this->light = l_; this->cor = c_; this->intensity = i_; }

		vec3 getNormal(point3 p_) {return this->light;};
};

class PointLight : public Light
{	
	public:
		PointLight(vec3 l_, color c_ = color(1,1,1), float i_ = 1.0)
		{ this->light = l_; this->cor = c_; this->intensity = i_; }

		vec3 getNormal(point3 p_) {return (this->light - p_);};
};

class FadingLight : public Light
{
	private:
		float kFading;
	public:
		FadingLight(vec3 l_, color c_ = color(1,1,1), float kF_ = 0.0, float i_ = 1.0)
		{ this->light = l_; this->cor = c_; this->kFading = kF_; this->intensity = i_; }

		vec3 getNormal(point3 p_) {return (this->light - p_);};

		// todo ->  colocar o fading no render e a equação é 1/d*d
		color getColor(point3 p_) 
		{
			float d = distance(p_, this->light);
			if( d >= kFading )
				return this->cor*(this->intensity*(1 - kFading/d));
			else return this->cor*0;
		};

};


#endif