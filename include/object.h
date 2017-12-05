#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <memory>
#include "ray.h"
#include "texture.h"
#include "transform.h"


class Material;
class Light;

typedef float real_type;


struct HitRecord{
	real_type t;
	vec3 normal;
	point3 p;
	std::shared_ptr<Material> material;
	bool negative = false;	
};

class Object{
	public:
		virtual ~Object() {}
		virtual bool hit(const Ray &ray,real_type t_min,real_type t_max, HitRecord &ht) const = 0;
		virtual void transform(double rotate[3], float scale, point3 translation) = 0;
		virtual void endTransform() = 0;
		virtual void setTexture(std::shared_ptr<Texture> t_) = 0;
};

#endif