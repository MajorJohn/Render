#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ray.h"
#include "material.h"

typedef float real_type;


struct HitRecord{
	real_type t;
	vec3 normal;
	point3 p;
	Material * material;
	bool negative = false;	
};

class Object{
	protected:
		

	public:
		virtual ~Object() {}
		virtual bool hit(const Ray &ray,real_type t_min,real_type t_max, HitRecord &ht) const = 0;
};

#endif