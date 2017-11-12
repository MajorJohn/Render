#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "object.h"
#include "material.h"

class Sphere: public Object{
	typedef float real_type;

	private:
		real_type radius;
		point3 center;		
		std::shared_ptr<Material> material;
		bool negative;

	public:

		Sphere(point3 c_= point3(), real_type r_= 0.0, std::shared_ptr<Material> m_ = nullptr, bool n_ = false) 
			: center(c_), radius(r_), material(m_), negative(n_) {}

		inline point3 getCenter(void) const { return center; }
		inline real_type getRadius(void) const { return radius; }

		bool hit(const Ray &ray, float t_min, float t_max, HitRecord &hr) const;
		void transform(double rotate[3], float scale, point3 translation) {};
		void endTransform() {};
};

#endif