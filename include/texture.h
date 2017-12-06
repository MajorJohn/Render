#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <math.h>
#include <memory>
#include "vec3.h"

class Texture 
{
	public:
		virtual color value(const vec3 & p = vec3(), float u = 0, float v = 0) const = 0;

};

class Constant_texture : public Texture 
{
	public:
		color rgb;

		//Constant_texture() {}
		Constant_texture(color c = color()) : rgb(c) {}

		virtual color value(const vec3 & p = vec3(), float u = 0, float v = 0) const 
		{
			return rgb;
		}
};

class Checker_texture : public Texture
{
	private:
		std::shared_ptr<Texture> odd;
		std::shared_ptr<Texture> even;
	
	public:

		Checker_texture(std::shared_ptr<Texture> o_ = std::make_shared<Constant_texture>(color(0,0,0)), std::shared_ptr<Texture> e_ = std::make_shared<Constant_texture>(color(1,1,1))) :
		odd(o_), even(e_) {}

		virtual color value(const vec3 & p = vec3(), float u = 0, float v = 0) const
		{
			float sines = sin(10*p.x()) *sin(10*p.y()) *sin(10*p.z());
			if(sines < 0)
				return odd->value(p);
			else
				return even->value(p);
		} 
};

#endif