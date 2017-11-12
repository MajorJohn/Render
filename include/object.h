#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ray.h"
#include <memory>

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
	protected:
		

	public:
		virtual ~Object() {}
		virtual bool hit(const Ray &ray,real_type t_min,real_type t_max, HitRecord &ht) const = 0;
		virtual void transform(double rotate[3], float scale, point3 translation) = 0;
		virtual void endTransform() = 0;
};

#endif